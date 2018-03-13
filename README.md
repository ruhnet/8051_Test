# 8051_Test
8051 Test code with 4 bit HD44780 LCD, LEDs, audio frequency generation.
I _DO NOT_ claim that the code is pretty or "correct." Just fiddling with some stuff :-)

YouTube video showing my breadboard and program operation: [Intel 8051 Microcontroller Test w External EPROM](https://www.youtube.com/watch?v=Z5JveB2_FQQ)



I compile with SDCC:
```
sdcc --iram-size 128 --stack-auto lcd.c
packihx lcd.ihx > lcd.hex
```

Since my EPROM programmer only handles raw hex data, no special formats, I also do: 
```
objcopy -I ihex -O binary lcd.hex lcd.bin
xxd -p lcd.bin lcd.bin.hex
```
Those two commands give me a raw binary file, and then convert that binary to the raw ascii hex. 


HD44780 LCD is hooked up to MCU as follows:

>LCD: DB4|DB5|DB6|DB7|EN |RS    RW
>P1:   0   1   2   3   4   5    GND 

LEDs and piezo buzzer or speaker are hooked to pins of P3. I used 2.7k has pullup resistors for the LCD lines on P1. I think 4.7k would be more correct but the 2.7ks were what I had handy.

My test circuit is on a breadboard, with external EPROM chip (27c64, but I also used 27256 and 27c512 with success).


