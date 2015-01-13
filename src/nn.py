import numpy as np

class NeuralNet:

    def __init__(self, layers, epsilon=0.154, learningRate = 0.1):
        '''
        Constructor
        Arguments:
          layers - a numpy array of L integers (L is # layers in the network)
          epsilon - one half the interval around zero for setting the initial weights
          learningRate - the learning rate for backpropagation
        '''
        self.layers = layers
        self.epsilon = epsilon
        self.learningRate = learningRate
        self.activation = None
        self.regLambda = 0.1
        
        # random.rand gives random number between 0,1, need between -eps, +eps
        length = len(layers)
        tht = np.empty((length-1), dtype = object)
        for i in range(0,length-1):
            tht[i]=np.random.rand(layers[i+1],layers[i]+1)            
        tht = tht * 2. * epsilon - epsilon
        self.theta = np.array([])
        for i in range(0,length-1):
            self.theta = np.append(self.theta, tht[i].flatten())
        

    def update(self, X, Y, a):
        '''
        Backpropagates and adjust weights based on assigned blame
        Arguments:
          X is a d-dimentional vector of inputs
          Y is a truth set of outputs
          a is the predicted outputs from propagation
        '''
        layers = self.layers
        epsilon = self.epsilon
        length = len(layers)
        
        # decode vector theta
        theta = np.empty((length-1),dtype=object)
        theta_vec = self.theta
        
        flag = 0        
        for i in range(0,length-1):
            size = layers[i+1] * (layers[i]+1)
            theta[i]=theta_vec[flag:(flag+size)].reshape(layers[i+1],-1)
            flag = flag+size
        
        # record vector for converge condition
        grad = np.empty((length-1), dtype=object)
        derivative = np.empty((length-1),dtype=object)
        
        # perform forward propogation
        error = np.empty((length),dtype=object)

        # activation 0~ l-1, with bias node
        activation = self.activation
        error[length-1] = a - Y.reshape(-1,1)
        # calculate error for each layer
        for j in range(length-2,0,-1):
            p1 = np.dot(theta[j].T,error[j+1])
            p2 = np.multiply(activation[j], (1-activation[j]))
            error[j]= np.multiply(p1,p2)
            if j > 1:
                error[j]= error[j][1:]
        
        #IMPORTANT: This step makes the network only update from non-zero observed outputs. Typical NN's do not do this.
        error[length-1][Y==0.0] == 0.0
        
        # calculate gradient
        grad[length-2] = np.dot(error[length-1],activation[length-2].T)
    
        for k in range(length-3,-1,-1):
            grad[k] = np.dot(error[k+1],activation[k].T)
            if k == 0:
                grad[k] = grad[k][1:,:]

        # compute partial derivative
        for i in range(length-2,-1,-1):
            row, col = theta[i].shape
            temp = np.c_[np.zeros((row,1)),self.regLambda * theta[i][:,1:]]
            derivative[i] = grad[i] + temp

        # update weights
        for i in range(0,length-1):
            theta[i] = theta[i] - self.learningRate * derivative[i]
    
        # unroll matrices into a single vector
        theta_vec = np.array([])
        for i in range(0,length-1):
            theta_vec = np.append(theta_vec, theta[i].flatten())

        # calculate cost func
        self.theta = np.copy(theta_vec)

              

    def propagate(self, X):
        '''
        Uses the model to predict weighted output values
        Arguments:
          X is a d-dimenstional numpy array
        Returns:
          a c-dimensional numpy array of the strength of each output
        '''
        layers = self.layers
        length = len(layers)
        
        # decode vector theta
        theta_mat = np.empty((length-1),dtype=object)

        flag = 0        
        for i in range(0,length-1):
            size = layers[i+1] * (layers[i]+1)
            theta_mat[i]=self.theta[flag:(flag+size)].reshape(layers[i+1],-1)
            flag = flag+size
                
        layerX = np.empty((length),dtype=object)
        
        # add bias node to layer0, now 1* d+1
        # need to use sigmoid func
        layerX[0] = X
        layerX[0] = np.append(1,layerX[0]).reshape(-1,1)
            
        for j in range(1,length):
            layerX[j] = self.sigmoid(np.dot(theta_mat[j-1],layerX[j-1]))
            # add bias node
            if j< (length -1) :
                layerX[j] = np.append(1,layerX[j]).reshape(-1,1)
        
        # store each layer
        self.activation = layerX
        output = layerX[length-1]
        
        return output
                
        
    
    def sigmoid(self, z):
        # return value of sigmoid function
        # z: n * 1 vector
        M = 1. + np.exp(-1. * z)
        result = np.divide(1.,M, dtype=float)
        
        for i in range(0,len(result)):
            if result[i] == 0:
                result[i] += 0.0001
        
        return result

    def propagateAndUpdate(self, x, y):
        '''
        Used to forward propagate a prediction based on input x, and update against truth y
        '''
        a = self.propagate(x)
        self.update(x, y, a)
        
