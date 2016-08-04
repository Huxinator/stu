define(
	['jquery', 'backbone', 'json', 'shipctl', 'list/commoditylist'],
	($, Backbone, json, Ship, CommodityList) ->
		ShipBeamView = Backbone.View.extend({

			initialize: ->

			getCommoditesFromModal: (modal) =>
				commodities = []
				$(modal).find('.beam_input').each (index, element) ->
					commodity_id = $(element).data('commodity-id')
					commodity_entry = {
						'commodity_id': $(element).data('commodity-id'),
						'amount': parseInt($(element).val())
					}
					commodities.push(commodity_entry)
				return commodities

			closeAndUpdate: (modal) ->
				ship = this.model
				$(modal).modal('hide')
				requirejs(['ship/storage'], (view) =>
					new view({model: ship}).render()
				)

			createModal: (storage, modal, beam_action) ->
				commodity_list = CommodityList.getList()
				for storage_item in storage.result
					do (storage_item) ->
						storage_item.name = commodity_list[storage_item.commodity_id]
						$("#modal_storage_table_body").loadTemplate('assets/html/ship/beam_item.html', storage_item, {append: true})
				$(modal).bind 'hidden.bs.modal', ->
					$(modal).remove()
				that = this
				$(modal).find('.beam_button').bind 'click', ->
					beam_action()
					that.closeAndUpdate(modal)
				$(modal).modal()
			
			render: (foreign_ship, way) ->
				ship = this.model
				that = this
				if way == 'from'
					json.request('ship.getStorageFromForeignShip', [ship.get('id'), foreign_ship.id], (storage) ->
						$(document.body).loadTemplate('assets/html/ship/beam_from_modal.html', foreign_ship, {append: true, afterInsert: (modal) ->
							that.createModal(storage, modal, ->
								Ship.beamFromShip(ship, foreign_ship, that.getCommoditesFromModal(modal))
							)
						})
					)
				else
					json.request('ship.getStorage', [ship.get('id')], (storage) ->
						$(document.body).parent().loadTemplate('assets/html/ship/beam_to_modal.html', foreign_ship, {append: true, afterInsert: (modal) ->
							that.createModal(storage, modal, ->
								Ship.beamToShip(ship, foreign_ship, that.getCommoditesFromModal(modal))
							)
						})
					)


		})

		return ShipBeamView
)
