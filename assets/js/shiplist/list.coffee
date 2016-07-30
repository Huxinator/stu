define(['jquery', 'json', 'jquery.tpl'], ($) ->
	return {
		render: ->
			requirejs(['helper/breadcrumb'], (breadcrumb) ->
				breadcrumb.update('Schiffliste');
			)
			json.request('shiplist.getList', [], (result) ->
				$("#content").loadTemplate('assets/html/shiplist/list.html', null, { afterInsert: ->
					for ship in result.result
						do (ship) ->
							$("#content").loadTemplate('assets/html/shiplist/item.html', ship, {append: true, afterInsert: (element) ->
								$(element).bind 'click', ->
									requirejs(['ship/hud'], (hud) ->
										hud.render(ship);
									)
							})
				})
			)
	}
)
