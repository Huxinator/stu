define(['jquery', 'json', 'jquery.tpl'], ($) ->
	return {
		render: (ship) ->
			json.request('ship.getDetails', [ship.id], (result) ->
				requirejs(['model/ship'], (model) ->
					ship = new model(result.result)
					requirejs(['helper/breadcrumb'], (breadcrumb) ->
						breadcrumb.update('Schiff / ' + ship.get('name'))
					)
					$("#content").loadTemplate('assets/html/ship/hud.html', ship.attributes, {afterInsert: ->
						requirejs(['ship/infobar'], (view) =>
							new view({model: ship}).render()
						)
						requirejs(['ship/shield'], (view) =>
							new view({model: ship}).render()
						)
						requirejs(['ship/map'], (view) =>
							new view({model: ship}).render()
						)
						requirejs(['ship/srs'], (view) =>
							new view({model: ship}).render()
						)
					})
				)
			)
	}
)
