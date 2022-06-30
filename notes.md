# Notes

## Lora data notes

The following code:

```
static void SetAppData(uint16_t data)
{
	appDataSize = 4;
	appData[0] = 0x01;
	appData[1] = 0x01;
	appData[2] = 0x01;
	appData[3] = 0x01;
}
```

Results in the receiving of this data: `AQIDBA==`

This is base64 encoding of: ``

## Device/Key stuff

Device EUI
00031d15033a0fe6
AppKey b9 54 35 cc 66 6b 08 48 c5 c3 95 7d 00 b8 56 f5
