# Arduino-Wire.h
Wire.h with timeout for Arduino.


### Tests:
Tested using generic DS3231 module with 32kbit EEPROM.

| Case | SDA | SCL | Power | Situation |
|---|---|---|---|---|
| 1 | disconnected | disconnected | connected    | as if no device |
| 2 | disconnected | connected    | connected    | address NACK detected |
| 3 | connected    | disconnected | connected    | address NACK detected |
| 4 | connected    | connected    | connected    | ideal case |
| 5 | disconnected | disconnected | disconnected | as if no device |
| 6 | disconnected | connected    | disconnected | **BLOCKS/HANGS** |
| 7 | connected    | disconnected | disconnected | **BLOCKS/HANGS** |
| 8 | connected    | connected    | disconnected | **BLOCKS/HANGS** |

If the SDA/SCL lines are accidentally disconnected the original Wire.h is able to detect the error. However if the power is cut, it blocks on the call to `Wire.endTransmission()`.

This version will instead return an error after a specified timeout.

To use just replace the #include directive to point to it. Then set the timeout using:

```C
  Wire.setTimeout( milliseconds );
```
Without setting the timeout it behaves exactly like the original version.

### Changes:

All while loops were changed to monitor timeout.

| Function | Changes |
|---|---|
| `twi_readFrom()` | returns 0 bytes read on timeout
| `twi_writeTo()`  | returns 4, which is described as "other twi error" in the original library |
| `twi_stop()`     | made to return a bool. returns false on timeout |
