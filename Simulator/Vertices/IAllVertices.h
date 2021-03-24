/**
 * @file IAllVertices.h
 * 
 * @ingroup Simulator/Vertices
 *
 * @brief An interface for vertices classes.
 */

#pragma once

using namespace std;

#include <iostream>

#include "Core/EdgeIndexMap.h"

class IAllEdges;

class Layout;

class IAllVertices {
public:
   virtual ~IAllVertices() {}

   ///  Setup the internal structure of the class.
   ///  Allocate memories to store all vertices' state.
   virtual void setupVertices() = 0;

   ///  Load member variables from configuration file.
   ///  Registered to OperationManager as Operation::loadParameters
   virtual void loadParameters() = 0;

   ///  Prints out all parameters of the vertices to logging file.
   ///  Registered to OperationManager as Operation::printParameters
   virtual void printParameters() const = 0;

   ///  Creates all the Vertices and assigns initial data for them.
   ///
   ///  @param  layout      Layout information of the neural network.
   virtual void createAllVertices(Layout *layout) = 0;

   ///  Outputs state of the vertex chosen as a string.
   ///
   ///  @param  i   index of the vertex (in vertices) to output info from.
   ///  @return the complete state of the vertex.
   virtual string toString(const int i) const = 0;

#if defined(USE_GPU)
   public:
       ///  Allocate GPU memories to store all vertices' states,
       ///  and copy them from host to GPU memory.
       ///
       ///  @param  allVerticesDevice   GPU address of the allVertices struct on device memory.
       virtual void allocNeuronDeviceStruct(void** allVerticesDevice) = 0;

       ///  Delete GPU memories.
       ///
       ///  @param  allVerticesDevice   GPU address of the allVertices struct on device memory.
       virtual void deleteNeuronDeviceStruct(void* allVerticesDevice) = 0;

       ///  Copy all vertices' data from host to device.
       ///
       ///  @param  allVerticesDevice   GPU address of the allVertices struct on device memory.
       virtual void copyNeuronHostToDevice(void* allVerticesDevice) = 0;

       ///  Copy all vertices' data from device to host.
       ///
       ///  @param  allVerticesDevice   GPU address of the allVertices struct on device memory.
       virtual void copyNeuronDeviceToHost(void* allVerticesDevice) = 0;

       ///  Update the state of all vertices for a time step
       ///  Notify outgoing synapses if vertex has fired.
       ///
       ///  @param  edges               Reference to the allEdges struct on host memory.
       ///  @param  allVerticesDevice       GPU address of the allVertices struct on device memory.
       ///  @param  allEdgesDevice      GPU address of the allEdges struct on device memory.
       ///  @param  randNoise              Reference to the random noise array.
       ///  @param  edgeIndexMapDevice  GPU address of the EdgeIndexMap on device memory.
       virtual void advanceVertices(IAllEdges &edges, void* allVerticesDevice, void* allEdgesDevice, float* randNoise, EdgeIndexMap* edgeIndexMapDevice) = 0;

       ///  Set some parameters used for advanceVerticesDevice.
       ///
       ///  @param  edges               Reference to the allEdges struct on host memory.
       virtual void setAdvanceVerticesDeviceParams(IAllEdges &edges) = 0;
#else // !defined(USE_GPU)
public:
   ///  Update internal state of the indexed Neuron (called by every simulation step).
   ///  Notify outgoing synapses if vertex has fired.
   ///
   ///  @param  edges         The Synapse list to search from.
   ///  @param  edgeIndexMap  Reference to the EdgeIndexMap.
   virtual void advanceVertices(IAllEdges &edges, const EdgeIndexMap *edgeIndexMap) = 0;

#endif // defined(USE_GPU)
};
