from odoo.tests.common import TransactionCase
from odoo.exceptions import UserError
from odoo.tests import tagged

@tagged('post_install', '-at_install')
class EstatePropertyTestCase(TransactionCase):

    @classmethod
    def setUpClass(cls):
        super(EstatePropertyTestCase, cls).setUpClass()
        
        # Create test properties
        cls.property_model = cls.env['estate.property']
        cls.property_offer_model = cls.env['estate.property.offer']
        
        # Create a property without offers
        cls.property_no_offers = cls.property_model.create({
            'name': 'Property Without Offers',
            'expected_price': 100000,
            'state': 'new'
        })
        
        # Create a sold property
        cls.sold_property = cls.property_model.create({
            'name': 'Already Sold Property',
            'expected_price': 200000,
            'state': 'sold'
        })
        
        # Create an offer for a property
        cls.property_with_offer = cls.property_model.create({
            'name': 'Property With Offer',
            'expected_price': 150000,
            'state': 'new'
        })
        cls.accepted_offer = cls.property_offer_model.create({
            'property_id': cls.property_with_offer.id,
            'price': 140000,
            'status': 'accepted'
        })

    def test_cannot_create_offer_for_sold_property(self):
        """Test that offers cannot be created for sold properties"""
        with self.assertRaises(UserError):
            self.property_offer_model.create({
                'property_id': self.sold_property.id,
                'price': 100000
            })

    def test_cannot_sell_property_without_accepted_offer(self):
        """Test that properties cannot be sold without an accepted offer"""
        with self.assertRaises(UserError):
            self.property_no_offers.action_sold()

    def test_successful_property_sale(self):
        """Test successful property sale with an accepted offer"""
        # Ensure the property with an accepted offer can be sold
        self.property_with_offer.action_sold()
        self.assertEqual(self.property_with_offer.state, 'sold', 
                         "Property should be marked as sold")

    def test_garden_reset(self):
        """Test that garden area and orientation are reset when garden is unchecked"""
        # Assuming there's a garden-related method or field
        test_property = self.property_model.create({
            'name': 'Garden Test Property',
            'garden': True,
            'garden_area': 50,
            'garden_orientation': 'North'
        })
        
        # Uncheck garden
        test_property.garden = False
        
        # Assert garden-related fields are reset
        self.assertEqual(test_property.garden_area, 0, 
                         "Garden area should be reset to 0")
        self.assertEqual(test_property.garden_orientation, False, 
                         "Garden orientation should be reset")