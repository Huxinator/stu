define(
	['jquery', 'backbone', 'json', 'bootstrap'],
	($, Backbone, json, Bootstrap) ->
		ShipSrsView = Backbone.View.extend({

			initialize: ->
				this.model.on('change', this.render, this);
			
			render: () ->
				ship = this.model
				$("#section_srs").loadTemplate('assets/html/ship/srs.html', null, { afterInsert: ->
					$("#srs_toggle_button").bind 'click', ->
						json.request('ship.toggleShortRangeScanner', [ship.get('id')], (result) ->
							ship.update(result.result)
						)

					if ship.get('srs_active') == 0
						$('#srs_toggle_button').text('aktivieren')
					else 
						$('#srs_toggle_button').text('deaktivieren')

					if ship.get('srs_active') == 1
						json.request('ship.getShipListByShipPosition', [ship.get('id')], (result) ->
							if result.result.length == 0
								$("#srs_table_body").loadTemplate('assets/html/ship/srs_empty.html')
							for foreign_ship in result.result
								do (foreign_ship) ->
									$("#srs_table_body").loadTemplate('assets/html/ship/srs_item.html', foreign_ship, {append: true, afterInsert: (element) ->
										$(element).find('.beamfrom').each (index, beam_from) ->
											$(beam_from).bind 'click', ->
												requirejs(['ship/beam_ship'], (view) =>
													new view({model: ship}).render(foreign_ship, 'from')
												)
										$(element).find('.beamto').each (index, beam_to) ->
											$(beam_to).bind 'click', ->
												requirejs(['ship/beam_ship'], (view) =>
													new view({model: ship}).render(foreign_ship, 'to')
												)
									})
						)
				})



		})

		return ShipSrsView
)
