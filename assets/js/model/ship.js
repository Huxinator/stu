define([
	'jquery',
	'backbone'
], ($, Backbone) ->
	var ShipModel = Backbone.Model.extend({
		initialize: (ship) ->
			for (var property in ship) {
				if (object.hasOwnProperty(property)) {
					this.set(property, ship.property);
				}
			}
	return ShipModel
});
