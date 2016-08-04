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
		beamToShip: (ship, foreign_ship, commodities) ->
			json.request('ship.beamToShip', [ship.get('id'), foreign_ship.id, commodities], (result) ->
				console.log(result)
			)
		beamFromShip: (ship, foreign_ship, commodities) ->
			json.request('ship.beamFromShip', [ship.get('id'), foreign_ship.id, commodities], (result) ->
				console.log(result)
			)
	}
)
