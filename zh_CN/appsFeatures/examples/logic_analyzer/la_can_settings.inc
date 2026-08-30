Here are the possible values for the decoder:

- **address_format** - Shifted = ``0``, Unshifted = ``1``
- **invert_bit** -  ``0, 1`` (invert input data signal)
- **decoder lines** - ``1 - 8`` (1 == DIO0_P)
- **trigger channel** - ``LA_T_CHANNEL_1 - LA_T_CHANNEL_8`` (1 == DIO0_P)

The possible decoded data packet types are:

- **Payload data** - Data payload (control value 0)
- **Start of frame** - Start of frame (SOF) bit, must be dominant (control value 1)
- **End of frame** - End of frame (EOF) bit, must be recessive (control value 2)
- **Identifier** - Identifier bits (control value 3)
- **Extended identifier** - Extended identifier bits (control value 4)
- **Full identifier** - Full identifier bits (control value 5)
- **Identifier extension bit** - Identifier extension bit (control value 6)
- **Reserved bit 0 and 1** - (control value 7)
- **Substitute remote request** - Substitute remote request (SRR) bit (control value 8)
- **Data length count** - Data length count bits (control value 9)
- **CRC delimiter** - CRC delimiter bit (control value 10)
- **ACK slot** - ACK slot bit (control value 11)
- **ACK delimiter** - ACK delimiter bit (control value 12)
- **Stuff bit** - Stuff bit (control value 13)
- **End of frame (EOF) must be 7 recessive bits** - (control value 14)
- **Identifier bits 10..4 must not be all recessive** - (control value 15)
- **CRC delimiter must be recessive** - (control value 16)
- **ACK delimiter must be recessive** - (control value 17)
- **Bit rate switch** - Bit rate switch (control value 18)
- **Error state indicator** - Error state indicator (control value 19)
- **Flexible data** - Flexible data (control value 20)
- **Stuff bit error** - Stuff bit error (control value 21)
- **CRC-15** - CRC-15 (control value 22)
- **CRC-17** - CRC-17 (control value 23)
- **CRC-21** - CRC-21 (control value 24)
- **Fixed stuff bit** - Fixed stuff bit (control value 25)
- **Stuff bits** - (control value 26)
- **SBC + FSB + CRC** - (control value 27)

Each decoded data packet has the following parameters:

- **control** - Data identifier.
- **data** - Data contained in the protocol.
- **line name** - Line name according to the protocol for which the data was decoded. Must be specified in the decoder settings, otherwise they will not be present.
- **sampleStart** - Starting position in the data to be recognized in samples. 0 = first sample, 1 = second sample, etc. The value is not an integer, since the bit width can be real depending on the protocol. Includes the pretrigger samples.
- **length** - Length of the recognized block in samples.
    
    .. math::

        \text{l_{packet}} = \frac{125~\mathrm{MHz}}{\text{decimation} \cdot \text{can_speed}} \cdot \text{bitsInPack}

- **bitsInPack** - Number of recognized data bits. Multiple of 0.5.