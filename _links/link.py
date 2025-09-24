
# External Links Configuration for Red Pitaya Documentation
# This file centralizes all external links for easy maintenance

# Common external links
EXTERNAL_LINKS = {
    # Red Pitaya related
    'redpitaya_website': 'https://redpitaya.com/',
    'redpitaya_github': 'https://github.com/RedPitaya/',
    'redpitaya_forum': 'https://forum.redpitaya.com/',
    'redpitaya_store': 'https://redpitaya.com/shop/',
    
    # Documentation and tutorials
    'sphinx_docs': 'https://www.sphinx-doc.org/en/master/',
    'readthedocs': 'https://readthedocs.org/',
    'myst_parser': 'https://myst-parser.readthedocs.io/',
    
    # Technical standards
    'ieee': 'https://www.ieee.org/',
    'ietf': 'https://www.ietf.org/',
    
    # Development tools
    'python': 'https://www.python.org/',
    'matplotlib': 'https://matplotlib.org/',
    'numpy': 'https://numpy.org/',
    'scipy': 'https://scipy.org/',
    
    # Hardware related
    'xilinx': 'https://www.xilinx.com/',
    'analog_devices': 'https://www.analog.com/',
    
    # Software tools
    'vivado': 'https://www.xilinx.com/products/design-tools/vivado.html',
    'quartus': 'https://www.intel.com/content/www/us/en/software/programmable/quartus-prime/',
    
    # Communication protocols
    'scpi_standard': 'https://www.ivifoundation.org/scpi/',
    'ethernet': 'https://en.wikipedia.org/wiki/Ethernet',
    'wifi': 'https://www.wi-fi.org/',
}

# Sphinx extlinks configuration
# This creates shortcuts like :rp-web:`text` that link to Red Pitaya website
SPHINX_EXTLINKS = {
    'rp-web': ('https://redpitaya.com/%s', 'Red Pitaya: %s'),
    'rp-github': ('https://github.com/RedPitaya/%s', 'GitHub: %s'),
    'rp-forum': ('https://forum.redpitaya.com/%s', 'Forum: %s'),
    'wikipedia': ('https://en.wikipedia.org/wiki/%s', 'Wikipedia: %s'),
    'github': ('https://github.com/%s', 'GitHub: %s'),
    'python-package': ('https://pypi.org/project/%s/', 'PyPI: %s'),
    'xilinx-doc': ('https://docs.xilinx.com/%s', 'Xilinx: %s'),
}
