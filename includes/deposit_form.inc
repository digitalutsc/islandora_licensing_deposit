<?php

/**
 * @file
 *  Deposit and License Form
 */

/**
 * Deposit and License Form
 *
 * @param array $form
 *   The Drupal form.
 * @param array $form_state
 *   The Drupal form state.
 * @param @args
 *
 * @return array
 *   A Drupal form definition.
 */

function islandora_licensing_deposit_form(array $form, array &$form_state, $args) {
  $selected_urls = $args;

  // Init agreement url
   $selected_url = array_values($selected_urls)[0];

  $selected_url = "http://google.com";

  $form['islandora_licensing_deposit_agreement'] = array(
    '#type' => 'select',
    '#title' => 'Deposit Agreement',
    '#description' => t('Deposit and Licensing Agreement. Please read carefully.'),
    '#options' => $selected_urls,
    '#ajax' => array(
      'callback' => 'the_callback',
      'wrapper' => 'href-div',
    ),
  );

  // City wrapper form element.
  $form['islandora_licensing_deposit_agreement_element_wrapper'] = array(
    '#prefix' => '<div id="divaroundseconddropdown">',
    '#suffix' => '</div>',
  );

  $form['islandora_licensing_deposit_agreement_link'] = array(
    '#type' => 'link',
    '#title' => t('Read Licensing/Deposit Agreement'),
    '#prefix' => '<div id="href-div">',
    '#suffix' => '</div>',
    '#href' => $selected_url,
    '#attributes' => array(
      'target' => "_blank",
    ),

  );

  $form["deposit_check"] = array(
    '#title' => 'Click here to agree:',
    '#type' => 'checkbox',
    '#required' => TRUE,
  );

  return $form;
}

function islandora_licensing_deposit_form_submit($form, &$form_state) {
  $selected_url = $form_state['values']['islandora_licensing_deposit_agreement'];
  $form_state['islandora']['shared_storage']['agreement_url'] = $selected_url;
}

function the_callback($form, &$form_state) {
  $selected_url = $form_state['values']['islandora_licensing_deposit_agreement'];
  $form['islandora_licensing_deposit_agreement_link']["#href"] =  $selected_url;

  return $form['islandora_licensing_deposit_agreement_link'];
}


