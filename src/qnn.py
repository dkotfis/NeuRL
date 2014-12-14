from nn import NeuralNet

import random
import numpy as np

class Experience():
    def __init__(self, s1, a1, r, s2, a2):
        '''
        Constructor
        '''
        self.s1 = s1
        self.s2 = s2
        self.a1 = a1
        #Note: Include the next action to use SARSA update rule
        self.a2 = a2
        self.r = r

class QNN():
    """
    Neural Q-Network. Includes experience replay.
    nactions: the number of actions
    input_size: the number of inputs
    max_experiences: the total number of experiences to save for replay
    gamma: future rewards discount rate
    alpha: learning rate for underlying NN
    use_sarsa: flag whether to use the SARSA update rule
    """
    def __call__(self,s,a=None):
        """ implement here the returned Qvalue of state (s) and action(a)
        e.g. Q.GetValue(s,a) is equivalent to Q(s,a)
        """
        if a==None:
            return self.GetValue(s)
        return self.GetValue(s,a)

    def __init__(self, nactions, input_size, max_experiences=500, gamma=0.6, alpha=0.1, use_sarsa=False):
        #Default uses 2 hidden layers of equal size
        lay = [input_size, int((nactions+input_size)/2.0), int((nactions+input_size)/2.0), nactions]
        self.nactions = nactions
        self.NN = NeuralNet(layers=lay, epsilon=0.154, learningRate=alpha)
        self.experiences = []
        self.max_experiences = max_experiences
        self.gamma = gamma
        self.use_sarsa = use_sarsa
        self.prob_remember = 0.1
        self.num_replay_samples = 10

    def GetValue(self, s, a=None):
        """ Return the Q(s,a) value of state (s) for action (a)
        or all values for Q(s)
        """
        out = self.NN.propagate(s)
        if (a==None):
            return out
        return out[a]

    def Update(self, s1, a1, r, s2, a2):
        """ update action value for action(a)
        """
        if (self.use_sarsa):
            v = r + self.gamma*self.GetValue(s2, a2)
        else:
            v = r + self.gamma*max(self.GetValue(s2))
        a = np.zeros(self.nactions)
        a[a1] = v
        self.NN.propagateAndUpdate(s1, a)

    def RememberExperience(self, s1, a1, r, s2, a2):
        if (random.random() < self.prob_remember):
            if (len(self.experiences) >= self.max_experiences):
                #TODO: Something more intelligent about how we determine what is worth forgetting
                self.experiences.pop(random.randint(0, self.max_experiences-1))
            self.experiences.append(Experience(s1, a1, r, s2, a2))

    def ExperienceReplay(self):
        #Skip until we have enough experience
        if (len(self.experiences) < self.num_replay_samples):
            return
        for i in xrange(self.num_replay_samples):
            index = random.randint(0, len(self.experiences)-1)
            exp = self.experiences[index]
            self.Update(exp.s1, exp.a1, exp.r, exp.s2, exp.a2)
