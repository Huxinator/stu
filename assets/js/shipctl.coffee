define(['jquery', 'json', 'jquery.notify', 'jquery.tpl', 'backbone'], ($, json) ->
	return {
		move: (ship, field_id) ->
			json.request('ship.move', [ship.id, field_id], (result) ->
				ship.cx = result.result.ship.cx
				ship.cy = result.result.ship.cy
				ship.energy = result.result.ship.energy
				requirejs(['ship/hud'], (hud) ->
					hud.render(ship)
				)
			)
	}
)
