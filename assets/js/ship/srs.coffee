define(
	['jquery', 'backbone', 'json', 'jquery.tpl', 'handlebars', 'bootstrap', 'shipctl', 'list/commoditylist'],
	($, Backbone, json, tpl, Handlebars, Bootstrap, Ship, CommodityList) ->
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

						json.request('ship.getShipListByShipPosition', [ship.get('id')], (result) ->
							if result.result.length == 0
								$("#srs_table_body").loadTemplate('assets/html/ship/srs_empty.html');
							for foreign_ship in result.result
								do (foreign_ship) ->
									$("#srs_table_body").loadTemplate('assets/html/ship/srs_item.html', foreign_ship, {append: true, afterInsert: (element) ->
										$(element).find('.beamfrom').each (index, beam_from) ->
											$(beam_from).bind 'click', ->
												$(beam_from).parent().loadTemplate('assets/html/ship/beam_from_modal.html', foreign_ship, {append: true, afterInsert: (modal) ->
													$(modal).modal()	
												})
										$(element).find('.beamto').each (index, beam_to) ->
											$(beam_to).bind 'click', ->
												json.request('ship.getStorage', [ship.get('id')], (storage) ->
													commodity_list = CommodityList.getList()
													$(beam_to).parent().loadTemplate('assets/html/ship/beam_to_modal.html', foreign_ship, {append: true, afterInsert: (modal) ->
														for storage_item in storage.result
															do (storage_item) ->
																storage_item.name = commodity_list[storage_item.commodity_id]
																$("#modal_storage_table_body").loadTemplate('assets/html/ship/beam_item.html', storage_item, {append: true})
														$(modal).bind 'hidden.bs.modal', ->
															$(modal).remove()
														$(modal).find('.beam_button').bind 'click', ->
															commodities = []
															$(modal).find('.beam_input').each (index, element) ->
																commodity_id = $(element).data('commodity-id')
																commodity_entry = {
																	'commodity_id': $(element).data('commodity-id'),
																	'amount': parseInt($(element).val())
																}
																commodities.push(commodity_entry)
															console.log('beeeam!')
															console.log(commodities)
															json.request('ship.beamToShip', [ship.get('id'), foreign_ship.id, commodities], (result) ->
																console.log(result)
															)
															$(modal).modal('hide')
														$(modal).modal()
													})
												)
									})
						)
				})



		})

		return ShipSrsView
)
