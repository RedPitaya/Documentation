
# Example of how to extend the external links
# This file shows how additional external links can be added

from link import EXTERNAL_LINKS, SPHINX_EXTLINKS

# Add more specific links
ADDITIONAL_LINKS = {
    'redpitaya_quickstart': 'https://redpitaya.com/Documentation/QuickStart/',
    'vivado_downloads': 'https://www.xilinx.com/support/download.html',
}

# Update the main dictionaries
EXTERNAL_LINKS.update(ADDITIONAL_LINKS)

# Add more extlinks patterns
ADDITIONAL_EXTLINKS = {
    'rp-doc': ('https://redpitaya.com/Documentation/%s', 'Red Pitaya Docs: %s'),
    'xilinx-download': ('https://www.xilinx.com/support/download/%s', 'Xilinx: %s'),
}

SPHINX_EXTLINKS.update(ADDITIONAL_EXTLINKS)
