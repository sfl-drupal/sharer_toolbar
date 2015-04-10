<?php

/**
 * @file sharer_toolbar.theme.inc
 * Theming functions
 */

/**
 * Sharer toolbar configuration form theming function.
 */
function theme_sharer_toolbar_config_form($variables) {
  $form = $variables['form'];

  // Define table header
  $header = array(
    t('Order'),
    t('Status'),
    t('Name'),
    t('Icon class'),
    t('Weight'),
  );

  // Render form rows as draggable table rows
  $rows = array();
  foreach (element_children($form['sharers']) as $sid) {
    $form['sharers'][$sid]['weight']['#attributes']['class'] = array('sharers-order-weight');
    $rows[] = array(
      'data' => array(
        array('class' => array('sharer-cross')),
        drupal_render($form['sharers'][$sid]['status']),
        drupal_render($form['sharers'][$sid]['name']),
        drupal_render($form['sharers'][$sid]['icon_class']),
        drupal_render($form['sharers'][$sid]['weight']),
      ),
      'class' => array('draggable'),
    );
  }

  // Render draggable table
  $output = drupal_render($form['note']);
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'sharers-order')));
  $output .= drupal_render_children($form);

  // Add draggable feature to table#sharers-order
  drupal_add_tabledrag('sharers-order', 'order', 'sibling', 'sharers-order-weight');

  return $output;
}
