define(
	['jquery', 'backbone', 'json', 'jquery.tpl', 'handlebars', 'shipctl'],
	($, Backbone, json, tpl, Handlebars, Ship) ->
		ShipMapView = Backbone.View.extend({

			initialize: ->
				# TODO poll the map
			
			render: () ->
				ship = this.model
				$("#section_map").loadTemplate('assets/html/ship/map.html')
				json.request('ship.getMap', [ship.id], (result) ->
					$.get('assets/html/map/field.html', (tpl) ->
						template = Handlebars.compile(tpl);
						fields = ''
						for cy, row_x of result.result
							for cx, map_field of row_x
								if !map_field
									map_field = { id: 0, type_id: 0, cx: cx, cy: cy}
								map_field.border = 0
								if map_field.cx == ship.get('cx') and map_field.cy == ship.get('cy')
									map_field.border = 1
								fields += template(map_field)
							fields += '<br />'

						$('#mapfields').html(fields)
						$('#mapfields').children('img').each (index, element) ->
							$(element).bind 'click', ->
								Ship.move(ship, $(element).data('id'))
					, 'html')
				)

		});

		return ShipMapView;
);
