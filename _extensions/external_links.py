# Custom external links management for Red Pitaya Documentation
# This creates RST substitutions for commonly used external links

import os
import sys

# Add the _links directory to the path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '_links'))

from link import EXTERNAL_LINKS

def setup_external_links(app):
    """Setup external links as RST substitutions"""
    
    # Create substitutions for external links
    substitutions = {}
    
    for key, url in EXTERNAL_LINKS.items():
        # Create a substitution that can be used as |key|
        substitutions[key] = url
        
        # Also create a link version |key_link|
        link_key = f"{key}_link"
        # Extract domain name for link text
        domain = url.split('/')[2].replace('www.', '').replace('.com', '').replace('.org', '').replace('.net', '')
        substitutions[link_key] = f"`{domain.title()} <{url}>`__"
    
    # Add substitutions to the app
    for key, value in substitutions.items():
        app.add_config_value(f'rst_epilog_{key}', f'.. |{key}| replace:: {value}', 'env')
    
    # Create the RST epilog (added to the end of every RST file)
    rst_epilog_parts = []
    for key, value in substitutions.items():
        rst_epilog_parts.append(f'.. |{key}| replace:: {value}')
    
    app.config.rst_epilog = '\n'.join(rst_epilog_parts)

def setup(app):
    """Sphinx extension setup function"""
    setup_external_links(app)
    return {
        'version': '1.0',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }
