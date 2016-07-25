$ ->
	$('#setting_username_button').click ->
		setting_username = $('#setting_username').val()
		if setting_username.length > 3
			json.request('settings.updateUserName', [setting_username], (result) ->
				$('#notification-container').notify(
					'create',
					'simple-notification',
					{
						title: 'Einstellungen gespeichert',
						text: 'AGGI'
					}
				);
			)
