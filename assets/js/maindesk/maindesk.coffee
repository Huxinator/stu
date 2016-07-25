define(['json', 'jquery.tpl'], ->
	return {
		render: ->
			json.request('maindesk.getCommonData', [], (response) ->
				result = response.result;
				$("#content").loadTemplate('assets/html/maindesk.html', {
					faction_img: 'assets/img/factions/'+result.faction_id+'.jpg',
					username: result.username
				});
			);
			requirejs(['helper/breadcrumb'], (breadcrumb) ->
				breadcrumb.update('Maindesk');
			);
			$('#main').hide();
			$('#page').show();
	}
);
