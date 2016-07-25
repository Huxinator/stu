define(['jquery'], ($) ->
	return {
		update: (title, event) ->
			$('#header_content').html(title);
			#$('#header_content').attr('rel', event.target.id);
	}
);
