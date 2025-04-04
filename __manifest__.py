{
    'name': 'Estate XML',
    'depends': ['base'],
    'data': [
        # First define base models
        'data/estate_property_model.xml',        # Define base property model first
        'views/estate_property_type_views.xml',  # Define type model 
        'views/estate_property_tag_views.xml',   # Define tag model
        'views/estate_property_offer_views.xml', # Define offer model
        
        # Then define additional fields that reference these models
        'data/estate_property_fields.xml',       # Property fields reference the above models
        
        # Then load data for the models
        'data/estate_property_type_data.xml',    # Load type data
        'data/estate_property_tag_data.xml',     # Load tag data
        'data/estate_property_data.xml',         # Load property data
        
        # Load security
        'security/ir.model.access.csv',
        
        # Finally load main views
        'views/estate_property_views.xml',       # Load main views
    ],
    'installable': True,
    'application': True,
    'auto_install': False,
}