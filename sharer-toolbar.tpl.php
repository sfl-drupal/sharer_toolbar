<?php

/**
 * @file sharer-toolbar.tpl.php
 * Template to present sharer toolbar
 */

?>
<div id="sharer-toolbar-container">
  <div id="sharer-toolbar"><?php print $title; ?></div>
  <ul id="sharer-toolbar">
    <?php foreach ($sharers as $sid => $sharer) : ?>
      <li class="shareLink__<?php print $sid; ?>">
        <a href="<?php print $sharer['url']; ?>" title="<?php print t($sharer['label']); ?>">
          <i class="<?php print $sharer['icon_class']; ?>"></i><?php print t($sharer['label']); ?>
        </a>
      </li>
    <?php endforeach; ?>
  </ul>
</div>