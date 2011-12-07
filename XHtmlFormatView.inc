<?php

/**
 * @file
 * Where reside the XHtmlFormatView, response format for services,
 * class implementation.
 */
class XHtmlFormatView extends RESTServerView {

  /**
   * Function called by RESTServer to display the ressource.
   * @return string
   */
  public function render() {
    $test = $this->model;
    return $this->renderXHtml($this->model);
  }

  /**
   * Specific sub rendering function
   * @param type $$content
   * @return type
   */
  protected function renderXHtml($content) {
    $out = '';
    if (is_array($content)) {
      foreach ($content as $element) {
        if ($this->isAstdClass($element)) {
          $out .= $this->renderstdClass($element);
        }
        else {
          $out .= print_r($element, TRUE);
        }
      }
    }
    elseif ($this->isAstdClass($content)) {
      $out = $this->renderstdClass($$content);
    }
    else {
      $out = print_r($content, TRUE);
    }
    return $out;
  }

  protected function isAstdClass($node) {
    $res = (version_compare(PHP_VERSION, '5.3.0') >= 0)
      ? is_a($node, 'stdClass')
      : ($node instanceof stdClass);
    return $res;
  }

  protected function renderstdClass($node) {
    return drupal_render(node_view($node));
  }

}
