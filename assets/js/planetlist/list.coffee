define(['jquery', 'json', 'jquery.tpl'], ($) ->
	return {
		render: ->
			requirejs(['helper/breadcrumb'], (breadcrumb) ->
				breadcrumb.update('Planetenliste');
			)
			json.request('planetlist.getList', [], (result) ->
				$("#content").loadTemplate('assets/html/planetlist/list.html', null, { afterInsert: ->
					for planet in result.result
						do (planet) ->
							$("#content").loadTemplate('assets/html/planetlist/item.html', planet, {append: true, afterInsert: (element) ->
								$(element).bind 'click', ->
									requirejs(['planet/overview'], (planet_overview) ->
										planet_overview.render(planet);
									)
							})
				})
			)
	}
)
