# Persian Text-to-Speech Engine for POS Devices

A lightweight, **rule-based Text-to-Speech (TTS) engine** written in C, designed to **convert numeric text and selected Persian words into speech** for **Point-of-Sale (POS) devices**. The system maps numbers and keywords to pre-recorded audio files and merges them into a single audio output for fast and reliable playback on embedded systems.

---

## Features

- Converts **numbers** (0 to billions) into Persian text and generates corresponding audio.
- Supports **selected keywords** for POS usage (e.g., “total”, “balance”, etc.).
- **Audio concatenation engine** to merge `.mp3` files into a single output.
- Designed for **low-resource devices**, ensuring fast and memory-efficient performance.
- Fully **modular C code** for easy extension and maintenance.

---

## File Structure

```
.
├── audio_files.c / audio_files.h  # Maps words to audio file paths
├── num2let.c                       # Converts numbers to Persian words
├── num2voice.c                     # Main program, generates output audio
├── audio/                           # Directory containing .mp3 files
├── README.md                        # Project documentation
```

---

## Getting Started

### Requirements

- C compiler (e.g., `gcc`)
- POS device or PC for testing
- Pre-recorded `.mp3` audio files for each number and keyword

### Build & Run

1. Compile the project:

```bash
gcc num2voice.c audio_files.c -o pos_tts
```

2. Run the program with a number as input:

```bash
./pos_tts 1250
```

3. The program will generate `output.mp3` containing the spoken number.

---

## How It Works

1. **Number Conversion:**  
   Converts numeric input into Persian text using `num2let.c`.

2. **Word Mapping:**  
   Each number word or keyword is mapped to its corresponding audio file in `audio_files.c`.

3. **Audio Merge:**  
   Concatenates individual audio files into a single `.mp3` output for playback.

---

## Example

Input: `1250`  
Output: `output.mp3` plays: `"یک هزار و دویست و پنجاه"`

---

## Future Improvements

- Add **full Persian TTS support** for arbitrary text.  
- Integrate **lightweight neural TTS models** for natural intonation.  
- Optimize **memory and processing** for ultra-low resource POS devices.  

---

## License

This project is released under the **MIT License**.
