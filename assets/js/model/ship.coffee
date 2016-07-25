define([
	'jquery',
	'backbone'
], ($, Backbone) ->
	ShipModel = Backbone.Model.extend({
		initialize: (ship) ->
			this.update(ship);

		update: (ship) ->
			$.each(ship, (key, value) =>
				this.set(key, value);
			);
	});
	return ShipModel;
);
