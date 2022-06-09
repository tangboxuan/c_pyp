#include <math.h>
#include "layer.h"

/* The sigmoid function and derivative. */
double sigmoid(double x)
{
  /**** PART 1 - QUESTION 1 ****/
  return 1.0 / (1.0 + exp(-x));
  /* 1 MARK */
}

double sigmoidprime(double x)
{
  return x*(1 - x);
}

/* Creates a single layer. */
layer_t *layer_create()
{
  /**** PART 1 - QUESTION 2 ****/
  layer_t *layer = calloc(1, sizeof(layer_t));
  if (layer == NULL) {
    return NULL;
  } else {
    return layer;
  }
  /* 2 MARKS */
}

/* Initialises the given layer. */
bool layer_init(layer_t *layer, int num_outputs, layer_t *prev)
{
  /**** PART 1 - QUESTION 3 ****/
  layer->num_outputs = num_outputs;
  layer->outputs = calloc(num_outputs, sizeof(double));
  layer->prev = prev;
  if (prev != NULL) {
    layer->num_inputs = prev->num_outputs;
    layer->weights = calloc(layer->num_inputs, sizeof(double));
    layer->biases = calloc(num_outputs, sizeof(double));
    layer->deltas = calloc(num_outputs, sizeof(double));
    if (layer->weights == NULL || layer->biases == NULL || layer->deltas == NULL) {
      return true;
    }
    for (int i = 0; i < layer->num_inputs; i++) {
      layer->weights[i] = calloc(num_outputs, sizeof(double));
      if (layer->weights[i] == NULL) {
        return true;
      }
      for (int j = 0; j < num_outputs; j++) {
        layer->weights[i][j] = ANN_RANDOM();
      }
    }
  }
  return false;
  /* 4 MARKS */
}

/* Frees a given layer. */
void layer_free(layer_t *layer)
{
  /**** PART 1 - QUESTION 4 ****/
  if (layer != NULL) {
    free(layer->outputs);
    if (layer->prev != NULL) {
      for (int i = 0; i < layer->num_inputs; i++) {
        free(layer->weights[i]);
      }
      free(layer->weights);
      free(layer->biases);
      free(layer->deltas);
    }
    free(layer);
  }
  /* 2 MARKS */
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer)
{
  /**** PART 1 - QUESTION 5 ****/
  /* objective: compute layer->outputs */
  if (layer->prev != NULL) { //check not input layer
    for (int j = 0; j < layer->num_outputs; j++) {
      double result = 0;
      for (int i = 0; i < layer->num_inputs; i++) {
        result += layer->weights[i][j] * layer->prev->outputs[i];
      }
      result += layer->biases[j];
      layer->outputs[j] = sigmoid(result);
    }
  }
  /* 3 MARKS */
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer)
{
  /**** PART 1 - QUESTION 6 ****/
  /* objective: compute layer->deltas */
  if (layer->next != NULL) { //check not output layer
    for (int i = 0; i < layer->num_outputs; i++) {
      double result = 0;
      for (int j = 0; j < layer->next->num_outputs; j++) {
        result += layer->next->weights[i][j] * layer->next->deltas[j];
      }
      layer->deltas[i] = sigmoidprime(layer->outputs[i]) * result;
    }
  }
  /* 2 MARKS */
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate)
{
  /**** PART 1 - QUESTION 7 ****/
  /* objective: update layer->weights and layer->biases */
  if (layer->prev != NULL) { //check not input layer
    for (int j = 0; j < layer->num_outputs; j++) {
      for (int i = 0; i < layer->num_inputs; i++) {
        layer->weights[i][j] += l_rate * layer->prev->outputs[i] * layer->deltas[j];
      }
      layer->biases[j] += l_rate * layer->deltas[j];
    }
  }
  /* 1 MARK */
}
