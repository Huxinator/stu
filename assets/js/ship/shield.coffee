define(
	['jquery', 'backbone', 'json', 'jquery.tpl'],
	($, Backbone) ->
		ShipShieldView = Backbone.View.extend({

			initialize: ->
				this.listenTo(this.model, "change", this.render);
			
			render: () ->
				ship = this.model;
				if ship.get('shield_active') == 0
					$("#section_shield").loadTemplate('assets/html/ship/shield.html', ship.attributes, { afterInsert: ->
						$("#activate_shield").bind 'click', ->
							json.request('ship.activateShield', [ship.get('id')], (result) ->
								ship.update(result.result);
							);
					});
				else
					$("#section_shield").loadTemplate('assets/html/ship/shield_active.html', ship.attributes, { afterInsert: ->
						$("#de_activate_shield").bind 'click', ->
							json.request('ship.deActivateShield', [ship.get('id')], (result) ->
								ship.update(result.result);
							);
					});
		});

		return ShipShieldView;
);
