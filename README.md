# chip8 emulator
This is an emulator (or more accurately, an *interpreter*) for the *interpreted* programming language [CHIP8](https://en.wikipedia.org/wiki/CHIP-8). 

## How to run
Requires Cmake 3.20, and [SDL3](https://wiki.libsdl.org/SDL3/FrontPage).
Legacy programs (~pre early-1990s) have different behavior. Run these with the ```-legacy``` flag.

### Testing
Current versions: [IBM](https://github.com/loktar00/chip8/blob/master/roms/IBM%20Logo.ch8) and [opcode](https://github.com/corax89/chip8-test-rom) tests.
You can run with ```./chip8 [file/path/rom.ch8]```

## Development
I followed this [tutorial](https://tobiasvl.github.io/blog/write-a-chip-8-emulator) for the spec. I thought it was very helpful because it's all conceptual and leaves you to figure out a lot on your own. I also used [@CoreDumped](https://www.youtube.com/@CoreDumpped) for a lot of the ground-up knowledge for how a computer works.

### Things that I learned:
- I strongly dislike [super primitives](https://www.w3schools.com/c/c_fixed_width_ints.php#:~:text=In%20C%2C%20the%20size%20of,Example)
- How did someone ever come up with this for the first time?
- It is (in hindsight) not that hard to make rocks think 

### Copyright
I mean what is there to copy even

