define([
	'jquery',
	'backbone',
	'json',
	'jquery.tpl'
], ($, Backbone) ->
	ShipInfoBarView = Backbone.View.extend({

		initialize: ->
			this.listenTo(this.model, "change", this.render);
		
		render: () ->
			$("#section_infobar").loadTemplate('assets/html/ship/infobar.html', this.model.attributes);
	});

	return ShipInfoBarView;
);
