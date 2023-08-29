#include "frame.h"

std::string IsoEncode(std::string& data) {
  const int kASCIIConst = 0x80;
  const int kBinaryMove = 6;
  const int kConvertConst = 0xc0;
  const int kAndOperationConst = 0x3f;

  std::string result;

  for (int i = 0; i < data.size(); ++i) {
    uint8_t ch = data[i];
    if (ch < kASCIIConst) {
      result.push_back(ch);
    } else {
      result.push_back(kConvertConst | ch >> kBinaryMove);
      result.push_back(kASCIIConst | (ch & kAndOperationConst));
    }
  }

  return result;
}

std::string UTF16LittleEndianEncode(std::string& data) {
  const int kByteSize = 8;
  const int kBytesAmount = 2;

  std::string buffer;
  std::string result;
  uint16_t buf;

  for (int i = kBytesAmount; i < data.size(); i += kBytesAmount) {
    uint16_t low = data[i];
    uint16_t high = data[i + 1];
    buf = (high << kByteSize) | low;
    result += static_cast<char>(buf);
  }

  return result;
}

std::string UTF16BigEndianEncode(std::string& data) {
  const int kByteSize = 8;
  const int kBytesAmount = 2;

  std::string buffer;
  std::string result;
  uint16_t buf;

  for (int i = kBytesAmount; i < data.size(); i += kBytesAmount) {
    uint16_t low = data[i];
    uint16_t hight = data[i + 1];
    buf = (low << kByteSize) | hight;
    result += static_cast<char>(buf);
  }

  return result;
}

/**
 * @brief Encodes a given string in the specified text encoding.
 * @param text_encoding 0 - ISO 1 - UTF16 Byte Order Mark 2 - UTF16
 * @param data A reference to the string to be encoded.
 * @return A new std::string object that contains the encoded data.
 */
std::string Encode(uint8_t text_encoding, std::string& data) {
  const int kMaxValue = 255;
  const int kMaxValueHex = 0xFF;

  if (text_encoding == kISOCode) {
      return (IsoEncode(data));
  } else if (text_encoding == kUTF16BOMCode) {
    int endian = data[0] & kMaxValueHex;
    if (endian == kMaxValue) {
      return UTF16LittleEndianEncode(data);
    } else {
      return UTF16BigEndianEncode(data);
    }
  } else if (text_encoding == kUTF16Code) {
    return UTF16BigEndianEncode(data);
  } else {
    return data;
  }
}

/**
*
*@brief Reads a line of code from a file with the specified encoding.
* @param text_encoding 0 - ISO 3 - UTF8
* @param file An input file stream object representing the file to read from.
* @param size An integer representing the number of bytes to read from the file. This is equal to the length of the line in bytes.
* @return A std::string object representing the line of code read from the file.
* @note If the text encoding is not ISO or UTF8, the function assumes that each character is represented by two bytes.
*/
std::string ReadCodeLine(uint8_t text_encoding, std::ifstream& file, int size) {
  std::string result;
  int i;

  if (text_encoding == kISOCode || text_encoding == kUTF8Code) {
    char sign;
    i = 0;
    while (i < size) {
      file.read(&sign, sizeof(sign));
      result += sign;
      i++;
    }
  } else {
    char sign1;
    char sign2;
    i = 0;
    while (i < size) {
      file.read(&sign1, sizeof(sign1));
      file.read(&sign2, sizeof(sign2));
      result = result + sign1 + sign2;
      i += 2;
    }
  }

  return result;
}

// Class definition

void ID3v2::ParseData(std::ifstream& stream) {

  const uint8_t kUnsyncMask = 0x80;
  const uint8_t kExtendedMask = 0x40;
  const uint8_t kExperimentalMask = 0x20;
  const uint8_t kFooterMask = 0x10;

  std::string buffer(kID3v2MaxDataSize, 0);

  stream.read(buffer.data(), kID3v2IdSize);
  id_ = buffer;

  stream.read(buffer.data(), kID3v2VersionSize);
  version_ = buffer;

  char flags;
  stream.read(&flags, kID3v2FlagsSize);

  unsync_ = (flags & kUnsyncMask);
  extended_ = (flags & kExtendedMask);
  experimental_ = (flags & kExperimentalMask) ;
  footer_ = (flags & kFooterMask);

  stream.read(buffer.data(), kID3v2LengthSize);
  for (int i = 0; i < kID3v2LengthSize; ++i) {
    size_ |= static_cast<uint32_t>(buffer[i] & 0x7F) << (7 * (kID3v2LengthSize - i - 1));
  }

};

void ID3v2::Read(const std::string& filename) {
  stream.open(filename, std::ios::binary);

  if (!stream.is_open()) {
    std::cout << "404 stream Not Found :(\n";
    return;
  }

  ParseData(stream);

  std::string header(kFrameHeaderSize, ' ');

  size_t counter = 0;

  while (counter < size_) {

    stream.read(&header[0], kFrameHeaderSize);
    std::string id = header.substr(0, kFrameIdSize);

    Frame* frame = nullptr;

    if (id[0] == 'T') {
      frame = new TextInformationFrames(header, stream);
    } else if (id[0] == 'W') {
      frame = new URLLinkFrames(header, stream);
    } else if (id == "UFID") {
      frame = new UniqueFileIdentifier(header, stream);
    } else if (id == "ETCO") {
      frame = new EventTimingCodes(header, stream);
    } else if (id == "USLT") {
      frame = new UnsynchronisedLyricsOrTextTranscription(header, stream);
    } else if (id == "SYLT") {
      frame = new SynchronisedLyricsOrText(header, stream);
    } else if (id == "COMM") {
      frame = new Comments(header, stream);
    } else if (id == "RVA2") {
      frame = new RelativeVolumeAdjustment(header, stream);
    } else if (id == "EQU2") {
      frame = new Equalisation(header, stream);
    } else if (id == "PCNT") {
      frame = new PlayCounter(header, stream);
    } else if (id == "POPM") {
      frame = new Popularimeter(header, stream);
    } else if (id == "RBUF") {
      frame = new RecommendedBufferSize(header, stream);
    } else if (id == "LINK") {
      frame = new LinkedInformation(header, stream);
    } else if (id == "POSS") {
      frame = new PositionSynchronisationFrame(header, stream);
    } else if (id == "USER") {
      frame = new TermsOfUseFrame(header, stream);
    } else if (id == "OWNE") {
      frame = new OwnershipFrame(header, stream);
    } else if (id == "COMR") {
      frame = new CommercialFrame(header, stream);
    } else if (id == "ENCR") {
      frame = new EncryptionMethodRegistration(header, stream);
    } else if (id == "GRID") {
      frame = new GroupIdentificationRegistration(header, stream);
    } else if (id == "PRIV") {
      frame = new PrivateFrame(header, stream);
    } else if (id == "SEEK") {
      frame = new SeekFrame(header, stream);
    } else {
      frame = new Frame(header, stream);
    }

    frames_.emplace_back(frame);

    counter += frame->GetSize() + kFrameHeaderSize;

  }

}

void ID3v2::Out() {
  if (!stream.is_open()) return;
  
  std::cout << "ID3v2 header:\n"; 
  std::cout << "  size: " << size_ << "\n";
  std::cout << "  unsync: " << unsync_ << "\n";
  std::cout << "  extended: " << extended_ << "\n";
  std::cout << "  experimental: " << experimental_ << "\n";
  std::cout << "  footer: " << footer_ << "\n";
  std::cout << "The header contains " << frames_.size() << " frames.\n\n";

  for (int i = 0; i < frames_.size(); ++i) {
    frames_[i]->Out();
  }
}

ID3v2::~ID3v2() {
  for (int i = frames_.size() - 1; i >= 0; --i) {
    delete(frames_[i]);
  }
}

Frame::Frame() {}

Frame::Frame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);
  stream.seekg(size_, std::ios_base::cur);
}

void Frame::ReadHeader(const std::string& header) {
  id_ = header.substr(0, kFrameIdSize);
  std::string buffer = header.substr(kFrameIdSize, kID3v2LengthSize);

  for (int i = 0; i < kID3v2LengthSize; ++i) {
    size_ |= static_cast<uint32_t>(buffer[i] & 0x7F) << (7 * (kID3v2LengthSize - i - 1));
  }

  strcpy(flags_, header.substr(kID3v2LengthSize + kFrameIdSize, kFrameFlagsSize).c_str());

}

void Frame::Out() {
}

int Frame::GetSize() { return size_; }

TextInformationFrames::TextInformationFrames(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  stream >> encode_;

  std::string line;
  line = ReadCodeLine(encode_, stream, GetSize() - 1);
  data_ = Encode(encode_, line);

}

void TextInformationFrames::Out() {
  std::cout << id_ << ": " << data_ << "\n";
}

URLLinkFrames::URLLinkFrames(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  // Make the frame do something with it's data.

  std::string data(size_, ' ');
  stream.read(&data[0], size_);

  url_ = data;
}

void URLLinkFrames::Out() {
  std::cout << id_ << ": " << url_ << "\n";
}

UniqueFileIdentifier::UniqueFileIdentifier(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  std::string data(size_, ' ');
  stream.read(&data[0], size_);

  owner_ = data.substr(0, data.find('\0'));
  data.erase(0, data.find('\0') + 1);
  identifier_ = data;

}

void UniqueFileIdentifier::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Owner: " << owner_ << "\n";
  std::cout << "  Identifier: " << identifier_ << "\n";
}

EventTimingCodes::EventTimingCodes(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  std::string data(size_, ' ');
  stream.read(&data[0], size_);

  uint8_t sign1;
  uint8_t sign2;
  size_t count;
  count = 0;

  stream >> format_;
  count++;

  while (count < size_) {
    stream >> sign1 >> sign2;
    events_.push_back(sign1);
    codes_.push_back(sign2);
    count += 2;
  }

}

void EventTimingCodes::Out() {
  std::cout << id_ << ":\n";
  for (int i = 0; i < events_.size(); ++i) {
    std::cout << "  Event:\n";
    std::cout << "    " << events_[i] << "\n";
    std::cout << "    " << codes_[i] << "\n";
  }
};

UnsynchronisedLyricsOrTextTranscription::UnsynchronisedLyricsOrTextTranscription(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  for (int i = 0; i < kLanguageSize; ++i) {
      stream >> sign;
      language_ += sign;
  }
  count += kLanguageSize;

  description_ = ReadCodeLine(encode_, stream, size_ - count);
  count += description_.size();
  if (encode_ == kISOCode || encode_ == kUTF8Code) {
      count += kISOAndUTF8End;
  } else {
      count += kUTF16End;
  }
  description_ = Encode(encode_, description_);

  lyrics_ = ReadCodeLine(encode_, stream, size_ - count);
  lyrics_ = Encode(encode_, lyrics_);
}

void UnsynchronisedLyricsOrTextTranscription::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Language: " << language_ << "\n";
  std::cout << "  Description: " << description_ << "\n";
  std::cout << "  Lyrics or Transcription: " << lyrics_ << "\n";
}

SynchronisedLyricsOrText::SynchronisedLyricsOrText(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  for (int i = 0; i < kLanguageSize; ++i) {
    stream >> sign;
    language_ += sign;
  }
  count += kLanguageSize;

  stream >> time_stamp_format_;
  stream >> content_type_;
  count += kUTF16End;

  content_description_ = ReadCodeLine(encode_, stream, size_ - count);
  content_description_ = Encode(encode_, content_description_);

}

void SynchronisedLyricsOrText::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Language: " << language_ << "\n";
  std::cout << "  Content type: " << content_type_ << "\n";
  std::cout << "  Content description: " << content_description_ << "\n";
}

Comments::Comments(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  for (int i = 0; i < kLanguageSize; ++i) {
    stream >> sign;
    language_ += sign;
  }
  count += kLanguageSize;

  description_ = ReadCodeLine(encode_, stream, size_ - count);
  count += description_.size();
  if (encode_ == kISOCode || encode_ == kUTF8Code) {
      count += kISOAndUTF8End;
  } else {
      count += kUTF16End;
  }
  description_ = Encode(encode_, description_);

  text_ = ReadCodeLine(encode_, stream, size_ - count);
  text_ = Encode(encode_, text_);
}

void Comments::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Language: " << language_ << "\n";
  std::cout << "  Description: " << description_ << "\n";
  std::cout << "  Text: " << text_ << "\n";
}

RelativeVolumeAdjustment::RelativeVolumeAdjustment(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kVolumeSize = 2;

  char sign;
  uint8_t number;
  size_t count;
  count = 0;

  stream >> sign;
  count++;
  while (sign != '\0') {
    identification_ += sign;
    stream >> sign;
    count++;
  }

  stream >> channel_;
  count++;

  for (int i = 0; i < kVolumeSize; ++i) {
    stream >> sign;
    volume_ += sign;
    count++;
  }

  stream >> bits_;
  count++;

  while (count < size_) {
    stream >> number;
    peak_volume_.push_back(number);
  }

}

void RelativeVolumeAdjustment::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Identification: " << identification_ << "\n";
  std::cout << "  Type of channel: " << channel_ << "\n";
  std::cout << "  Volume adjustment: " << volume_ << "\n";
  std::cout << "  Bits representing peak: " << bits_ << "\n";
  std::cout << "  Peak volume: ";
  for (int i = 0; i < peak_volume_.size(); ++i) {
    std::cout << peak_volume_[i] << " ";
  }
  std::cout << "\n";
}

Equalisation::Equalisation(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kFrequencySize = 2;
  const int kVolumeAdjusmentSize = 2;

  char sign;
  std::string buffer;

  stream >> interpolation_method_;

  stream >> sign;
  while (sign != '\0') {
      identification_ += sign;
      stream >> sign;
  }

  buffer = "";
  for (int i = 0; i < kFrequencySize; ++i) {
      stream >> sign;
      buffer += sign;
  }
  frequency_ = std::stoi(buffer);

  buffer = "";
  for (int i = 0; i < kVolumeAdjusmentSize; ++i) {
      stream >> sign;
      buffer += sign;
  }
  volume_adjusment_ = std::stoi(buffer);
}

void Equalisation::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Interpolation method: " << interpolation_method_ << "\n";
  std::cout << "  Identification: " << identification_ << "\n";
  std::cout << "  Frequency: " << frequency_ << "\n";
  std::cout << "  Volume adjustment: " << volume_adjusment_ << "\n";
}

PlayCounter::PlayCounter(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  std::string buffer(GetSize(), ' ');
  stream.read(&buffer[0], GetSize());
  count_ = std::stoi(buffer);
}

void PlayCounter::Out() {
  std::cout << id_ << ": " << count_ << "\n";
}

Popularimeter::Popularimeter(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kBinaryMove = 8;

  char sign;
  size_t count;
  count = 0;
  std::string buffer;

  stream >> sign;
  count++;
  while (sign != '\0') {
    email_ += sign;
    stream >> sign;
    count++;
  }

  stream >> rating_;

  buffer = "";
  while (count < size_) {
    stream >> sign;
    buffer += sign;
    count++;
  }

  for (int i = 0; i < buffer.size(); ++i) {
    counter_ += buffer[buffer.size() - 1 - i] << (kBinaryMove * i);
  }
}

void Popularimeter::Out() {
  std::cout << id_ << ": " << counter_ << "\n";
}

RecommendedBufferSize::RecommendedBufferSize(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kBufferSize = 2;
  const int kOffsetSize = 2;
  const int kOffsetIndex = 1;
  const int kBinaryMove = 8;

  char sign;
  std::string buffer;

  buffer = "";
  for (int i = 0; i < kBufferSize; ++i) {
    stream >> sign;
    buffer += sign;
  }
  buffer_size_ = std::stoi(buffer);

  stream >> info_flag_;

  buffer = "";
  for (int i = 0; i < kOffsetSize; ++i) {
    stream >> sign;
    buffer += sign;
  }
  for (int i = 0; i < kOffsetSize; ++i) {
    offset_ += buffer[kOffsetIndex - i] << (kBinaryMove * i);
  }

}

void RecommendedBufferSize::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Buffer size: " << buffer_size_ << "\n";
  std::cout << "  Info flag: " << info_flag_ << "\n";
  std::cout << "  Offset: " << offset_ << "\n";
}

LinkedInformation::LinkedInformation(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kIdentifierSize = 4;

  char sign;
  size_t count;
  count = 0;

  for (int i = 0; i < kIdentifierSize; ++i) {
      stream >> sign;
      identifier_ += sign;
      count++;
  }

  stream >> sign;
  count++;
  while (sign != '\0') {
    url_ += sign;
    stream >> sign;
    count++;
  }

  while (count < size_) {
    stream >> sign;
    data_ += sign;
    count++;
  }
}

void LinkedInformation::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Frame identifier: " << identifier_ << "\n";
  std::cout << "  url: " << url_ << "\n";
  std::cout << "  Other data: " << data_ << "\n";
}

PositionSynchronisationFrame::PositionSynchronisationFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  uint8_t number;
  size_t count;
  count = 0;

  stream >> format_;
  count++;

  while (count < size_) {
    stream >> number;
    position_.push_back(number);
  }
}

void PositionSynchronisationFrame::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  Time stamp format: " << format_ << "\n";
  std::cout << "  Position: ";
  for (int i = 0; i < position_.size(); ++i) {
      std::cout << position_[i] << " ";
  }
  std::cout << "\n";
}

TermsOfUseFrame::TermsOfUseFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  for (int i = 0; i < kLanguageSize; ++i) {
    stream >> sign;
    language_ += sign;
    count++;
  }

  text_ = ReadCodeLine(encode_, stream, size_ - count);
  text_ = Encode(encode_, text_);
}

void TermsOfUseFrame::Out() {

}

OwnershipFrame::OwnershipFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  stream >> sign;
  count++;
  while (sign != '\0') {
    price_ += sign;
    stream >> sign;
    count++;
  }

  for (int i = 0; i < kDateSize; ++i) {
    stream >> sign;
    date_ += sign;
    count++;
  }

  seller_ = ReadCodeLine(encode_, stream, size_ - count);
  seller_ = Encode(encode_, seller_);
}

void OwnershipFrame::Out() {

}

CommercialFrame::CommercialFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t length;
  length = GetSize();
  size_t count;
  count = 0;

  stream >> encode_;
  count++;

  stream >> sign;
  count++;
  while (sign != '\0') {
    price_ += sign;
    stream >> sign;
    count++;
  }

  for (int i = 0; i < kDateSize; ++i) {
    stream >> sign;
    valid_until_ += sign;
    count++;
  }

  stream >> sign;
  count++;
  while (sign != '\0') {
    price_ += sign;
    stream >> sign;
    count++;
  }

  stream >> received_;
  count++;

  seller_ = ReadCodeLine(encode_, stream, length - count);
  count += seller_.size();
  if (encode_ == kISOCode || encode_ == kUTF8Code) {
    count += kISOAndUTF8End;
  } else {
    count += kUTF16End;
  }
  seller_ = Encode(encode_, seller_);

  description_ = ReadCodeLine(encode_, stream, length - count);
  count += description_.size();
  if (encode_ == kISOCode || encode_ == kUTF8Code) {
    count += kISOAndUTF8End;
  } else {
    count += kUTF16End;
  }
  description_ = Encode(encode_, seller_);

  stream >> sign;
  count++;
  while (sign != '\0') {
    picture_type_ += sign;
    stream >> sign;
    count++;
  }

  while (count < length) {
    stream >> sign;
    logo_ += sign;
    count++;
  }
}

void CommercialFrame::Out() {

}

RegistrationFrame::RegistrationFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> sign;
  count++;
  while (sign != '\0') {
    owner_ += sign;
    stream >> sign;
    count++;
  }

  stream >> type_;
  count++;
  while (count < size_) {
    stream >> sign;
    data_ += sign;
    count++;
  }

}

void EncryptionMethodRegistration::Out() {
  std::cout << id_ << "\n";
  std::cout << "      Owner identifier_: " << owner_ << "\n";
  std::cout << "      Method symbol: " << type_ << "\n";
  std::cout << "      Encryption data_: " << data_ << "\n";
}

void GroupIdentificationRegistration::Out() {
  std::cout << id_ << "\n";
  std::cout << "      Owner identifier_: " << owner_ << "\n";
  std::cout << "      Group symbol: " << type_ << "\n";
  std::cout << "      Group dependent data_: " << data_ << "\n";
}

PrivateFrame::PrivateFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  char sign;
  size_t count;
  count = 0;

  stream >> sign;
  count++;
  while (sign != '\0') {
    owner_ += sign;
    stream >> sign;
    count++;
  }

  while (count < size_) {
    stream >> sign;
    data_ += sign;
    count++;
  }

}

void PrivateFrame::Out() {
  std::cout << id_ << ":\n";
  std::cout << "  owner: " << owner_ << "\n";
  std::cout << "  data: " << data_ << "\n";
}

SeekFrame::SeekFrame(const std::string& header, std::ifstream& stream) {
  ReadHeader(header);

  const int kOffsetSize = 4;

  std::string buffer;
  char sign;

  buffer = "";
  for (int i = 0; i < kOffsetSize; ++i) {
    stream >> sign;
    buffer += sign;
  }
  offset_ = std::stoi(buffer);
  
}

void SeekFrame::Out() {
  std::cout << id_ << ": " << offset_ << "\n";
}