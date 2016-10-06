# Tape encode

Encode a binary file in raw PCM format (8-bit) to create tapes
(hopefully) compatible with the ZX spectrum and the like.


## Encoding 101

- The data is encoded using only two "levels", ``0x00`` and ``0xff``
- A "zero" bit is encoded as a "high" of duration T, followed by a "low" of the same duration
- A "one" bit is encoded as a "high" of duration 2T, followed by a "low" of the same duration

Typical durations for a zero are ~244µs "high" followed by ~244µs
"low"; this allows transmitting 2047 zeroes per second.

Typical durations for a one are ~489µs "high" followed by ~489µs
"low"; this allows transmitting 1023 ones per second.

Using two samples to represent a zero, and four to represent a one,
this gives us a sample rate of 4096Hz.


## Building

The thing is ~50 lines of C, and should compile just fine by running
``make``.


## Usage

Pipe your data to the built executable:

    ./tapencode < /tmp/kittens.jpg


## Listening to the generated audio

Since the produced audio is in raw PCM format, you need to specify all
the parameters manually:

    mpv --demuxer=rawaudio --demuxer-rawaudio-channels=1 --demuxer-rawaudio-rate=4096 --demuxer-rawaudio-format=u8 -

(One channel, 4096kHz sample rate, 8-bit integers)

You can adjust the sample rate; 4096 should be the one typically used
on old tapes.

If you want to encode that as a mp3 file, just append
``--out=/tmp/kittens.mp3``. MPV will figure out the desired type by
the file extension.


## TODO

- Generate "alignment" codes for the tape
- Generate WAV header (cannot do that streaming though!)
  - Or generate a mp3 directly on the fly?
  - Or maybe not, there are tools to convert from PCM anyways
