# WordCount Utility

		A simple utility for counting lines, words and characters.

- [Usage](#usage)
- [Features](#features)
- [Examples](#examples)
- [Deadline](#deadline)

## Usage

![](https://s4.gifyu.com/images/demoecd70c91f2089499.gif)

```
arguments:  
            -l --lines display line count in file
            -m --chars display line count in file
            -w --words display word count in file
            -c --bytes display file size
            -h --help display help
```

## Features

✅ **-l, --lines**    output number of lines

✅ **-c, --bytes**    output filesize in bytes

✅ **-w, --words**    outputs word count

✅ **-m, --chars**     outputs char count

✅ **-h, --help**     outputs list of commands and description
  
## Examples

### General example
```
$ wordcount [ arguments ] [ files.. ]
```

### Get line count, word count, filesize
```
$ wordcount filename
```
Output:

	lines words bytes filename

### Get line count, word count, filesize for 2 files
```
$ wordcount filename1 filename2
```
Output:

	lines words bytes filename1
	lines words bytes filename2

### Get line conut, word count, charcater count
```
$ wordcount filename1 -lwm
```
Output:

	lines words chars filename1


## Deadline 

1. 25.09.22 24:00 - 0.8
2. 02.10.22 24:00 - 0.65
3. 09.10.22 24:00 - 0.5



