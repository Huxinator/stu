define(
	['jquery', 'backbone', 'json', 'jquery.tpl'],
	($, Backbone) ->
		ShipShieldView = Backbone.View.extend({

			initialize: ->
				this.listenTo(this.model, "change", this.render);
			
			render: () ->
				ship = this.model;
				$("#section_shield").loadTemplate('assets/html/ship/shield.html', ship.attributes, { afterInsert: ->
					if ship.get('shield_active') == 1
						action = 'ship.deActivateShield'
						$('#shield_data').addClass('shield_active')
						shield_toggle_button_text = 'Schilde deaktivieren'
					else
						action = 'ship.activateShield'
						shield_toggle_button_text = 'Schilde aktivieren'
					$('#shield_toggle_button').text(shield_toggle_button_text)

					$("#shield_toggle_button").bind 'click', ->
						json.request(action, [ship.get('id')], (result) ->
							$('#shield_data').toggleClass('shield_active')
							ship.update(result.result)
						);
				});
		});

		return ShipShieldView;
);
