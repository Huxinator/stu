define(['jquery', 'json', 'jquery.tpl'], ($) ->
	return {
		render: ->
			$("#content_main").loadTemplate('assets/html/login.html', null, {
				success: ->
					$('#login_button').bind 'click', ->
						json.request('external.login', [$('#login_email').val(), $('#login_password').val()], ->
							$('#main').hide();
							$('#page').show();
							requirejs(['maindesk/maindesk'], (maindesk) ->
								maindesk.render()
							);
						);
					});
	}
);
