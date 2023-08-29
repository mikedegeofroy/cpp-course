#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

const int kID3v2IdSize = 3;
const int kID3v2VersionSize = 2;
const int kID3v2FlagsSize = 1;
const int kID3v2LengthSize = 4;
const int kID3v2MaxDataSize = 4;
const int kFrameIdSize = 4;
const int kFrameFlagsSize = 2;
const int kFrameLengthSize = 4;
const int kFrameHeaderSize = 10;

const int kISOCode = 0;
const int kUTF16BOMCode = 1;
const int kUTF16Code = 2;
const int kUTF8Code = 3;
const int kISOAndUTF8End = 1;
const int kUTF16End = 2;
const int kLanguageSize = 3;
const int kDateSize = 8;

// Class declaration

class Frame {
  protected:
    std::string id_;
    int size_ = 0;
    char flags_[2];
    std::string data;

  public:
    Frame();
    Frame(const std::string& header, std::ifstream& stream);
    void ReadHeader(const std::string& header);
    int GetSize();

    virtual void Out();

};

class UniqueFileIdentifier : public Frame {
  public:
    UniqueFileIdentifier(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string owner_;
    std::string identifier_;
};

class TextInformationFrames : public Frame {
  public:
    TextInformationFrames(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    char encode_;
    std::string data_;
};

class URLLinkFrames : public Frame {
  public:
    URLLinkFrames(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string url_;
};

class EventTimingCodes : public Frame {
  public:
    EventTimingCodes(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t format_;
    std::vector<uint8_t> events_;
    std::vector<uint8_t> codes_;
};

class UnsynchronisedLyricsOrTextTranscription : public Frame {
  public:
    UnsynchronisedLyricsOrTextTranscription(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t encode_;
    std::string language_;
    std::string description_;
    std::string lyrics_;
};

class SynchronisedLyricsOrText : public Frame {
  public:
    SynchronisedLyricsOrText(const std::string& header, std::ifstream& stream);
    void Out() override;
    
  protected:
    uint8_t encode_;
    std::string language_;
    uint8_t time_stamp_format_;
    uint8_t content_type_;
    std::string content_description_;
};

class Comments : public Frame {
  public:
    Comments(const std::string& header, std::ifstream& stream);
    void Out() override;

  private:
    uint8_t encode_;
    std::string language_;
    std::string description_;
    std::string text_;
};

class RelativeVolumeAdjustment : public Frame {
  public:
    RelativeVolumeAdjustment(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string identification_;
    uint8_t channel_;
    std::string volume_;
    uint8_t bits_;
    std::vector<uint8_t> peak_volume_;
};

class Equalisation : public Frame {
  public:
    Equalisation(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t interpolation_method_;
    std::string identification_;
    int16_t frequency_;
    int16_t volume_adjusment_;
};

class PlayCounter : public Frame {
  public:
    PlayCounter(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    size_t count_;
};

class Popularimeter : public Frame {
  public:
    Popularimeter(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string email_;
    uint8_t rating_;
    size_t counter_;
};

class RecommendedBufferSize : public Frame {
  public:
    RecommendedBufferSize(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint32_t buffer_size_;
    char info_flag_;
    uint32_t offset_;
};

class LinkedInformation : public Frame {
  public:
    LinkedInformation(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string identifier_;
    std::string url_;
    std::string data_;
};

class PositionSynchronisationFrame : public Frame {
  public:
    PositionSynchronisationFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t format_;
    std::vector<uint8_t> position_;
};

class TermsOfUseFrame : public Frame {
  public:
    TermsOfUseFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t encode_;
    std::string language_;
    std::string text_;
};

class OwnershipFrame : public Frame {
  public:
    OwnershipFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t encode_;
    std::string price_;
    std::string date_;
    std::string seller_;
};

class CommercialFrame : public Frame {
  public:
    CommercialFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint8_t encode_;
    std::string price_;
    std::string valid_until_;
    std::string contact_;
    uint8_t received_;
    std::string seller_;
    std::string description_;
    std::string picture_type_;
    std::string logo_;
};

class RegistrationFrame : public Frame {
  public:
    RegistrationFrame(const std::string& header, std::ifstream& stream);
  protected:
    std::string owner_;
    char type_;
    std::string data_;
};

class EncryptionMethodRegistration : public RegistrationFrame {
  using RegistrationFrame::RegistrationFrame;
  public:
    void Out() override;
};

class GroupIdentificationRegistration : public RegistrationFrame {
  using RegistrationFrame::RegistrationFrame;
  public:
    void Out() override;
};

class PrivateFrame : public Frame {
  public:
    PrivateFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    std::string owner_;
    std::string data_;
};

class SeekFrame : public Frame {
  public:
    SeekFrame(const std::string& header, std::ifstream& stream);
    void Out() override;

  protected:
    uint32_t offset_;
};

class ID3v2 {
  private:
    void ParseData(std::ifstream& stream);

  protected:
    std::string id_;
    std::string version_;
    
    bool unsync_;
    bool extended_;
    bool experimental_;
    bool footer_;

    int size_ = 0;

    std::vector<Frame*> frames_;
    std::ifstream stream;

  public:
    ~ID3v2();
    void Out();
    void Read(const std::string& filename);
};
