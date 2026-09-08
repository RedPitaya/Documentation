Here are the possible values for the decoder:

- **address_format** - Shifted = ``0``, Unshifted = ``1``
- **invert_bit** -  ``0, 1`` (invert input data signal)
- **decoder lines** - ``1 - 8`` (1 == DIO0_P)
- **trigger channel** - ``LA_T_CHANNEL_1 - LA_T_CHANNEL_8`` (1 == DIO0_P)

The possible decoded data packet types are:

- **Start** - The start bit of the I2C message (control value 0)
- **Repeat start** - The repeat start bit of the I2C message (control value 1)
- **Stop** -The stop bit of the I2C message (control value 2)
- **Ack** - The acknowledge bit of the I2C message (control value 3)
- **Nack** - The not acknowledge bit of the I2C message (control value 4)
- **Read address** - The address of the I2C device (control value 5)
- **Write address** - The address of the I2C device (control value 6)
- **Read data** - The data read from the I2C device (control value 7)
- **Write data** - The data written to the I2C device (control value 8)

Each decoded data packet has the following parameters:

- **control** - Data identifier.
- **data** - Data contained in the protocol.
- **line name** - Line name according to the protocol for which the data was decoded. Must be specified in the decoder settings, otherwise they will not be present.
- **sampleStart** - Starting position in the data to be recognized in samples. 0 = first sample, 1 = second sample, etc. The value is not an integer, since the bit width can be real depending on the protocol. Includes the pretrigger samples.
- **length** - Length of the recognized block in samples.
    
    .. math::

        \text{l_{packet}} = \frac{125~\mathrm{MHz}}{\text{decimation} \cdot \text{i2c_speed}} \cdot \text{bitsInPack}

- **bitsInPack** - Number of recognized data bits. Multiple of 0.5.