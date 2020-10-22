import torch
import torch.nn as nn
import torch.utils.data as data
import architecture

if torch.cuda.is_available():
    device='cuda'
else:
    device='cpu'

learning_rate=0.001
training_epochs=1
batch_size=10

mnist_train, mnist_test=architecture.mnist_dataset()
data_loader=data.DataLoader(dataset=mnist_train, batch_size=batch_size, shuffle=True, drop_last=True)

model=architecture.CNN().to(device)

criterion=nn.CrossEntropyLoss().to(device)
optimizer=torch.optim.Adam(model.parameters(), lr=learning_rate)

total_batch=len(data_loader)
print('Learning started. It takes sometime.')
for epoch in range(training_epochs):
    avg_cost=0
    for X, Y in data_loader:
        X=X.to(device)
        Y=Y.to(device)

        optimizer.zero_grad()
        hypothesis=model(X)
        cost=criterion(hypothesis, Y)
        cost.backward()
        optimizer.step()

        avg_cost += cost/total_batch
    print('[Epoch: {:>4}] cost={:>.9}'.format(epoch+1, avg_cost))

print('Learning Finished!')

architecture.test_CNN(mnist_test, model, device)