define(
	['jquery', 'backbone', 'json', 'jquery.tpl', 'handlebars', 'shipctl', 'list/commoditylist'],
	($, Backbone, json, tpl, Handlebars, Ship, CommodityList) ->
		ShipStorageView = Backbone.View.extend({

			initialize: ->
			
			render: () ->
				ship = this.model
				commodity_list = CommodityList.getList()
				$("#section_storage").loadTemplate('assets/html/ship/storage.html', null, { afterInsert: ->
					json.request('ship.getStorage', [ship.get('id')], (result) ->
						for storage_item in result.result
							do (storage_item) ->
								storage_item.name = commodity_list[storage_item.commodity_id]
								$("#storage_table_body").loadTemplate('assets/html/ship/storage_item.html', storage_item, {append: true})
					)
				})



		})

		return ShipStorageView
)
