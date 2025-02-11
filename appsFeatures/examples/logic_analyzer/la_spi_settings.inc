Here are the possible values for the decoder:

- **bit order** - MSB_FIRST = ``0``, LSB_FIRST = ``1``
- **cpha** -  ``0, 1``
- **cpol** -  ``0, 1``
- **invert** -  ``0, 1`` (invert input data signal)
- **number of data bits** - ``7, 8``
- **cs polarity** - ActiveLow = ``0``, ActiveHigh = ``1``
- **decoder lines** - ``1 - 8`` (1 == DIO0_P)
- **trigger channel** - ``LA_T_CHANNEL_1 - LA_T_CHANNEL_8`` (1 == DIO0_P)

.. note::

    Here is a conversion between Red Pitaya SPI modes and CPHA and CPOL:

    - LISL - Low  idle level, sample on leading edge  - cpol=0, cpha=0
    - LIST - Low  idle level, sample on trailing edge - cpol=0, cpha=1
    - HISL - High idle level, sample on leading edge  - cpol=1, cpha=0
    - HIST - High idle level, sample on trailing edge - cpol=1, cpha=1

The possible decoded data packet types are:

- **Data** - the data bits of the SPI message (control value 0)

Each decoded data packet has the following parameters:

- **control** - Data identifier.
- **data** - Data contained in the protocol.
- **line name** - Line name according to the protocol for which the data was decoded. Must be specified in the decoder settings, otherwise they will not be present.
- **sampleStart** - Starting position in the data to be recognized in samples. 0 = first sample, 1 = second sample, etc. The value is not an integer, since the bit width can be real depending on the protocol. Includes the pretrigger samples.
- **length** - Length of the recognized block in samples.
    
    .. math::

        \text{l_{packet}} = \frac{125~\mathrm{MHz}}{\text{decimation} \cdot \text{spi_speed}} \cdot \text{bitsInPack}

- **bitsInPack** - Number of recognized data bits. Multiple of 0.5.