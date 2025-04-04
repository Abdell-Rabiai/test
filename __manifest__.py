{
    'name': 'Estate XML',
    'depends': ['base'],
    'data': [
        'data/estate_property_fields.xml',  # Load model fields
        'views/estate_property_type_views.xml',  # Load menu
        'views/estate_property_tag_views.xml',  # Load menu
        'views/estate_property_offer_views.xml',  # Load menu
        
        'data/estate_property_type_data.xml',  # Load data
        'data/estate_property_tag_data.xml',  # Load data
        'data/estate_property_data.xml',  # Load data
        
        
        # 'views/report_estate_property.xml',  # Load report
        # 'views/report_estate_property_offers.xml',  # Load report
        # Then load security
        'security/ir.model.access.csv',
        # 'security/property_rules.xml',
        'views/estate_property_views.xml',  # Load views
    ],
    'installable': True,
    'application': True,
    'auto_install': False,
}