$(document).ready(function() {
	$('#register_button').click(function() {
		json.request('external.register', [$('#register_email').val(),$('form input[name=register_faction_id]:checked').val()], function(response) {
			$('#register_alert').html(response.result);
			$('#register_alert').show();
		});
	});

	$('#register_email').blur(function() {
		address = $('#register_email').val();
		if (address.length > 1) {
			json.request('external.checkEmail', [address], function(response) {
				$('#register_email_check').removeClass().addClass('glyphicon glyphicon-ok');
				$('#register_email_check_message').html(response.result);
			}, function(response) {
				$('#register_email_check').removeClass().addClass('glyphicon glyphicon-remove');
				$('#register_email_check_message').html(response.error.message);
			});
		}
	});

	json.request('external.getFactionList', [], function(response) {
		result = response.result;
		jQuery.each(result.factions, function(key, faction) {
			$('#factionlist').loadTemplate(
				$('#factioninfo'),
				{
					name: faction.name,
					id: faction.id
				},
				{
					append: true
				}
			);
		});
	});
});
