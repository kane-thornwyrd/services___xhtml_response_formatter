<?php

/**
 * @file
 * Where reside the XHtmlFormatView, response format for services, class implementation.
 */
class XHtmlFormatView extends RESTServerView {

  public function render() {
    $test = $this->model;
    return $this->render_xhtml($this->model);
  }

  protected function render_xhtml($node) {
    $out = '';
    if (is_array($node)) {
      foreach ($node as $n) {
        if ($this->_is_a_node($n)) {
          $out .= $this->_render_node($n);
        }
        else {
          $out .= print_r($n, TRUE);
        }
      }
    }
    elseif ($this->_is_a_node($node)) {
      $out = $this->_render_node($node);
    }
    else {
      $out = print_r($node, TRUE);
    }
    return $out;
  }

  protected function _is_a_node($node) {
    $res = (version_compare(PHP_VERSION, '5.3.0') >= 0)
      ? is_a($node, 'stdClass')
      : ($node instanceof stdClass);
    return $res;
  }

  protected function _render_node($node) {
    return drupal_render(node_view($node));
  }

}