
# External Links Configuration for Red Pitaya Documentation
# This file centralizes all external links for easy maintenance
# Links used 2+ times across documentation should be added here

# Common external links - used for global substitutions in conf.py
EXTERNAL_LINKS = {
    # Red Pitaya infrastructure
    'redpitaya_website': 'https://redpitaya.com/',
    'redpitaya_github': 'https://github.com/RedPitaya/',
    'redpitaya_downloads': 'https://downloads.redpitaya.com/',
    'redpitaya_forum': 'https://forum.redpitaya.com/',
    'redpitaya_store': 'https://redpitaya.com/shop/',
    'redpitaya_contact': 'https://redpitaya.com/contact-us/',
    
    # Development tools - Windows
    'winscp': 'https://winscp.net/eng/index.php',
    'putty': 'http://www.putty.org',
    'ftdi_driver': 'http://www.ftdichip.com/Drivers/VCP.htm',
    
    # Development tools - Cross-platform
    'vscode': 'https://code.visualstudio.com/',
    'vscode_workspace': 'https://code.visualstudio.com/docs/editor/workspaces',
    'vscode_tutorials': 'https://code.visualstudio.com/docs/getstarted/introvideos',
    'vscode_python_env': 'https://code.visualstudio.com/docs/python/environments',
    
    # SD Card tools
    'balena_etcher': 'https://www.balena.io/etcher/',
    'applepi_baker': 'https://www.tweaking4all.com/hardware/raspberry-pi/applepi-baker-v2',
    
    # Python ecosystem
    'python_downloads': 'https://www.python.org/downloads/',
    'numpy': 'https://numpy.org/',
    'matplotlib': 'https://matplotlib.org/',
    'scipy': 'https://scipy.org/',
    'pyvisa': 'https://pyvisa.readthedocs.io/en/latest/',
    'pyvisa_py': 'https://pyvisa.readthedocs.io/projects/pyvisa-py/en/latest/',
    
    # Documentation tools
    'sphinx_docs': 'https://www.sphinx-doc.org/en/master/',
    'readthedocs': 'https://readthedocs.org/',
    'myst_parser': 'https://myst-parser.readthedocs.io/',
    'markdown': 'https://en.wikipedia.org/wiki/Markdown',
    'markdown_daringfireball': 'https://daringfireball.net/projects/markdown/syntax',
    'mathjax': 'https://www.mathjax.org/',
    'json': 'https://www.json.org/',
    'json_wiki': 'https://en.wikipedia.org/wiki/JSON',
    'nbconvert': 'https://nbconvert.readthedocs.io/en/latest/',
    
    # Linux tools
    'minicom': 'https://linux.die.net/man/1/minicom',
    'screen': 'https://www.gnu.org/software/screen/manual/screen.html',
    'wsl': 'https://learn.microsoft.com/en-us/windows/wsl/install',
    'wsl_usb': 'https://learn.microsoft.com/en-us/windows/wsl/connect-usb',
    
    # Hardware vendors
    'xilinx': 'https://www.xilinx.com/',
    'analog_devices': 'https://www.analog.com/',
    'texas_instruments': 'https://www.ti.com/',
    'microchip': 'https://www.microchip.com/',
    'digikey': 'https://www.digikey.com/',
    'renesas': 'https://www.renesas.com/',
    'seeed_grove': 'https://wiki.seeedstudio.com/Grove_System/',
    'seeed_temp_sensor': 'https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/',
    'seeed_motion_sensor': 'https://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor',
    'seeed_touch_sensor': 'https://wiki.seeedstudio.com/Grove-Touch_Sensor',
    'seeed_button': 'https://wiki.seeedstudio.com/Grove-Button',
    'seeed_switch': 'https://wiki.seeedstudio.com/Grove-Switch-P',
    'seeed_tilt': 'https://wiki.seeedstudio.com/Grove-Tilt_Switch',
    'seeed_potentiometer': 'https://wiki.seeedstudio.com/Grove-Slide_Potentiometer',
    
    # FPGA tools
    'vivado': 'https://www.xilinx.com/products/design-tools/vivado.html',
    'vivado_downloads': 'https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools.html',
    'vivado_downloads_archive': 'https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive.html',
    'amd_login': 'https://login.amd.com/',
    'quartus': 'https://www.intel.com/content/www/us/en/software/programmable/quartus-prime/',
    'xilinx_device_tree': 'https://github.com/Xilinx/device-tree-xlnx',
    
    # Communication protocols & standards
    'scpi_standard': 'https://www.ivifoundation.org/scpi/',
    'ethernet': 'https://en.wikipedia.org/wiki/Ethernet',
    'wifi': 'https://www.wi-fi.org/',
    'ieee': 'https://www.ieee.org/',
    'ietf': 'https://www.ietf.org/',
    
    # Third-party Red Pitaya projects
    'pavel_demin_notes': 'https://github.com/pavel-demin/red-pitaya-notes',
    'linien': 'https://github.com/linien-org/linien',
    'pyrpl': 'https://pyrpl.readthedocs.io/en/latest/',
    'marcelo_lock_in': 'https://marceluda.github.io/rp_lock-in_pid/',
    'jupyter_cadquery': 'https://github.com/bernhard-42/jupyter-cadquery',
    
    # Media & community
    'audacity': 'https://www.audacityteam.org',
    'youtube': 'https://www.youtube.com/',
    
    # Other tools & documentation
    'wikihow_refresh': 'https://www.wikihow.com/Force-Refresh-in-Your-Internet-Browser',
    'wiki_dhcp': 'https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol',
    'wiki_network_socket': 'https://en.wikipedia.org/wiki/Network_socket',
    'wiki_arbitrary_waveform': 'https://en.wikipedia.org/wiki/Arbitrary_waveform_generator',
    'wiki_subnet': 'https://en.wikipedia.org/wiki/Subnet',
    'wiki_ip_address': 'https://en.wikipedia.org/wiki/IP_address',
    'mikroe_mcp2542': 'https://www.mikroe.com/mcp2542-click',
    'css_electronics_can': 'https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial',
    'smbus_specs': 'http://smbus.org/specs/',
    'digilent_spi': 'https://digilent.com/blog/wp-content/uploads/2018/09/SPI_timing_diagram.svg_.png',
}

# Sphinx extlinks configuration
# This creates shortcuts like :rp-web:`text` that link to Red Pitaya website
# Use these for links with variable paths (e.g., different product pages, GitHub paths)
SPHINX_EXTLINKS = {
    # Red Pitaya infrastructure
    'rp-web': ('https://redpitaya.com/%s', 'Red Pitaya: %s'),
    'rp-github': ('https://github.com/RedPitaya/%s', 'GitHub: %s'),
    'rp-forum': ('https://forum.redpitaya.com/%s', 'Forum: %s'),
    'rp-download': ('https://downloads.redpitaya.com/%s', 'Red Pitaya Downloads: %s'),
    'rp-store': ('https://redpitaya.com/shop/%s', 'Red Pitaya Store: %s'),
    
    # General external services
    'wikipedia': ('https://en.wikipedia.org/wiki/%s', 'Wikipedia: %s'),
    'github': ('https://github.com/%s', 'GitHub: %s'),
    'youtube-video': ('https://www.youtube.com/watch?v=%s', 'YouTube: %s'),
    'python-package': ('https://pypi.org/project/%s/', 'PyPI: %s'),
    'xilinx-doc': ('https://docs.xilinx.com/%s', 'Xilinx: %s'),
}
