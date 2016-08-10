requirejs.config({
	shim: {
		'bootstrap': {
			deps: ['jquery']
		},
		'jquery.tpl': {
			deps: ['jquery']
		},
		'jquery.jsonrpc': {
			deps: ['jquery']
		},
		'jquery.ui': {
			deps: ['jquery']
		},
		'jquery.notify': {
			deps: ['jquery.ui']
		},
		'json': {
			deps: ['jquery.jsonrpc'],
			exports: 'json'
		},
		'backbone': {
			deps: ['underscore']
		}
	}
	paths: {
		'jquery': '../lib/jquery',
		'jquery.tpl': '../lib/jquery-tpl',
		'jquery.jsonrpc': '../lib/jquery.jsonrpc',
		'jquery.ui': '../lib/jquery-ui',
		'jquery.notify': '../lib/jquery.notify.min',
		'bootstrap': '../lib/bootstrap',
		'json': '../lib/json',
		'backbone': '../lib/backbone-min',
		'underscore': '../lib/underscore-min',
		'handlebars': '../../../node_modules/handlebars/dist/handlebars.min',
		'shipctl': 'shipctl',
		'list': 'list'

	}
});

requirejs(['jquery', 'json', 'jquery.notify', 'jquery.tpl', 'backbone'], ($, json) ->
	json.setup();

	$.ajaxSetup({
		cache: true
	});

	$('#header_content').click ->
		$('#'+$('#header_content').attr('rel')).trigger('click');

	$('#notification-container').notify({
		speed: 500,
		expires: 3000
	});	

	loadLinks();

	$('#page').hide();
	$('#main').show();
	
	requirejs(['login/login'], (loginapp) ->
		loginapp.render()
	);

);


initPage = ->
	$('#maindesk_link').trigger('click');

setHeaderContent = (title, event) ->
	$('#header_content').html(title);
	$('#header_content').attr('rel', event.target.id);

showMainDesk = (event) ->
		json.request('maindesk.getCommonData', [], (response) ->
			result = response.result;
			$("#content").loadTemplate('assets/html/maindesk.html', {
				faction_img: 'assets/img/factions/'+result.faction_id+'.jpg',
				username: result.username
			});
		);
		setHeaderContent('Maindesk', event);
		$('#main').hide();
		$('#page').show();

loadLinks = () ->
	$('#maindesk_link').bind 'click', (event) ->
		showMainDesk(event)

	$('#maindesk_link_ext').bind 'click', (event) ->
		showMainDesk(event)
	
	$('#settings_link').bind 'click', (event) ->
		json.request('user.getData', [], (response) ->
			result = response.result;
			$("#content").loadTemplate('assets/html/settings.html', {
				username: result.username,
				email: result.email,
			});
		);
		setHeaderContent('Einstellungen', event);

	$('#navbar_link').bind 'click', -> 
		$('#maindesk_link').trigger('click');	

	$('#registration_link').bind 'click', ->
		$("#content_main").loadTemplate('assets/html/register.html', {});

	$('#nav_ship_link').bind 'click', ->
		requirejs(['shiplist/list'], (shiplistapp) ->
			shiplistapp.render();
		)
	$('#nav_planet_link').bind 'click', ->
		requirejs(['planetlist/list'], (planetlistapp) ->
			planetlistapp.render()
		)
