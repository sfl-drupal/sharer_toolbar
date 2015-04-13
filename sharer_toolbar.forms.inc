<?php

/**
 * @file sharer_toolbar.forms.inc
 * Forms configuration
 */

/**
 * Sharer toolbar configuration form.
 */
function sharer_toolbar_config_form($form, &$form_state) {
  module_load_include('inc', 'sharer_toolbar');

  // To make checkboxes sortable
  $form['#tree'] = TRUE;

  // List all available sharers
  $sharers = _sharer_toolbar_get_ordered_available_sharers();
  $sharers_configuration = variable_get('sharer_toolbar_sharers_configuration', array());
  foreach ($sharers as $delta => $sharer) {
    $sid = $sharer['sid'];
    $sharer_conf = (isset($sharers_configuration[$sid])) ? $sharers_configuration[$sid] : array();

    // Checkbox to activate or not sharer.
    $form['sharers'][$sid]['status'] = array(
      '#type' => 'checkbox',
      '#default_value' => (isset($sharer_conf['status'])) ? $sharer_conf['status'] : 0,
    );

    // Textfield to hold sharer name.
    $form['sharers'][$sid]['name'] = array(
      '#type' => 'textfield',
      '#default_value' => (isset($sharer_conf['name'])) ? $sharer_conf['name'] : $sharer['name'],
    );

    // Textfield to hold sharer icon class.
    $icon_value = (isset($sharer_conf['icon_class'])) ? $sharer_conf['icon_class'] : $sharer['icon_class'];
    $form['sharers'][$sid]['icon_class'] = array(
      '#type' => 'textfield',
      '#default_value' => $icon_value,
      '#field_prefix' => '<i class="' . $icon_value . '"></i>',
    );

    // Textfield to hold sharer label.
    $form['sharers'][$sid]['label'] = array(
      '#type' => 'textfield',
      '#default_value' => (isset($sharer_conf['label'])) ? $sharer_conf['label'] : $sharer['label'],
    );

    // Invisible field, but contains sort info (weights).
    $form['sharers'][$sid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $delta,
    );
  }

  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}


/**
 * Sharer toolbar configuration form submit.
 */
function sharer_toolbar_config_form_submit($form, &$form_state) {
  $sharers = $form_state['values']['sharers'];
  $sharers_order = array();
  $sharers_configuration = array();

  // Iterate on orders to store informations
  foreach ($sharers as $sid => $sharer_conf) {

    // Store weight
    $sharers_order[$sharer_conf['weight']] = $sid;

    // Store configuration
    $sharers_configuration[$sid] = array(
      'name' => $sharer_conf['name'],
      'icon_class' => $sharer_conf['icon_class'],
      'status' => $sharer_conf['status'],
    );
  }

  // Save values
  variable_set('sharer_toolbar_sharers_order', $sharers_order);
  variable_set('sharer_toolbar_sharers_configuration', $sharers_configuration);

  // Confirmation
  drupal_set_message(t('Sharer toolbar configuration has been saved.'));
}
