
/**
 * @file sharer-opener.js
 * Opening sharer link in new window
 */

(function ($) {
  Drupal.behaviors.sharerOpener = {
    attach: function (context, settings) {
      $('#sharer-toolbar-list', context).find('.shareLink__link').click(function () {

        // Parse URL to get protocol
        var parser = document.createElement('a');
        parser.href = $(this).attr('href');

        // Open popup if protocol is different from «mailto»
        if (parser.protocol !== 'mailto:') {
          window.open($(this).attr('href'), $(this).data('title'), "width=640, height=480");
          return false;
        }
      });
    }
  };
})(jQuery);
