import pandas as pd
import torch
from torch import nn
import matplotlib.pyplot as plt

x=torch.arange(1, 11, dtype=torch.float).unsqueeze(dim=1)
y=x/2+1+torch.randn(10).unsqueeze(dim=1)/5
print(x,y)
data=torch.cat((x,y), dim=1)
data=pd.DataFrame(data.numpy())
data.to_csv('Model_Data.csv', header=['x', 'y'])

data=pd.read_csv('Model_Data.csv')

x=torch.from_numpy(data['x'].values).unsqueeze(1).float()
y=torch.from_numpy(data['y'].values).unsqueeze(1).float()
#plt.xlim(0, 11)
#plt.ylim(0, 8)
#plt.scatter(x, y)
#plt.title('Model_Data')
#plt.show()

model=nn.Linear(in_features=1, out_features=1, bias=True)

criterion=nn.MSELoss()
optimizer=torch.optim.Adam(params=model.parameters(), lr=0.01)
print(model(x))

for step in range(500):
    prediction=model(x)
    loss=criterion(input=prediction, target=y)
    print(step, loss.detach())
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

def display_results(model, x, y):
    prediction=model(x)
    loss=criterion(input=prediction, target=y)

    plt.clf()
    plt.xlim(0, 11)
    plt.ylim(0,8)
    plt.scatter(x.data.numpy(), y.data.numpy())
    plt.plot(x.data.numpy(), prediction.data.numpy(), 'b--')
    plt.title('loss={:.4}, w={:.4}, b={:.4}'.format(loss.data.item(), model.weight.data.item(), model.bias.data.item()))
    plt.show()

torch.save(obj=model, f='Linear Regression Model.pt')

loaded_model=torch.load(f='Linear Regression Model.pt')
display_results(loaded_model, x, y)