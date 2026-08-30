Here are the possible values for the decoder:

- **baudrate** - ``1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600``
- **bit order** - LSB_FIRST = ``0``, MSB_FIRST = ``1``
- **invert** -  ``0, 1`` (invert input data signal)
- **number of data bits** - ``5, 6, 7, 8, 9``
- **number of stop bits** - STOP_BITS_NO = ``0``, STOP_BITS_05 = ``1``, STOP_BITS_10 = ``2``, STOP_BITS_15 = ``3``, STOP_BITS_20 = ``4``
- **parity** - NONE = ``0``, EVEN = ``1``, ODD = ``2``, ALWAYS_0 = ``3``, ALWAYS_1 = ``4``
- **decoder lines** - ``1 - 8`` (1 == DIO0_P)
- **trigger channel** - ``LA_T_CHANNEL_1 - LA_T_CHANNEL_8`` (1 == DIO0_P)

The possible decoded data packet types are:

- **Parity bit error** - the parity bit of the UART message is not detected (control value 0)
- **Start bit error** - the start bit of the UART message is not detected (control value 1)
- **Stop bit error** - the stop bit of the UART message is not detected (control value 2)
- **Data** - the data bits of the UART message (control value 3)
- **Start bit** - the start bit of the UART message (control value 4)
- **Stop ok** - the stop bit of the UART message (control value 5)
- **Parity bit** - the parity bit of the UART message (control value 6)

Each packet has the following parameters:

- **control** - Data identifier.
- **data** - Data contained in the protocol.
- **line name** - Line name according to the protocol for which the data was decoded. Must be specified in the decoder settings, otherwise they will not be present.
- **sampleStart** - Starting position in the data to be recognized in samples. 0 = first sample, 1 = second sample, etc. The value is not an integer, since the bit width can be real depending on the protocol. Includes the pretrigger samples.
- **length** - Length of the recognized block in samples.
    
    .. math::

        \text{l_{packet}} = \frac{125~\mathrm{MHz}}{\text{decimation} \cdot \text{uart_baudrate}} \cdot \text{bitsInPack}

- **bitsInPack** - Number of recognized data bits. Multiple of 0.5.