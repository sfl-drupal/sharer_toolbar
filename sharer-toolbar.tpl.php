<?php

/**
 * @file sharer-toolbar.tpl.php
 * Template to present sharer toolbar
 */

?>
<div id="sharer-toolbar-container" class="shareLink">
  <button id="sharer-toolbar-btn" class="shareLink__trigger"><?php print t($title); ?></button>
  <ul id="sharer-toolbar-list"  class="shareLink__list">
    <?php foreach ($sharers as $sid => $sharer) : ?>
      <li class="shareLink__item shareLink__item--<?php print $sid; ?>">
        <a class="shareLink__link shareLink__link--<?php print $sid; ?>" href="<?php print $sharer['url']; ?>" data-title="<?php print t($sharer['label']); ?>">
          <i class="<?php print $sharer['icon_class']; ?>"></i><?php print t($sharer['label']); ?>
        </a>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
