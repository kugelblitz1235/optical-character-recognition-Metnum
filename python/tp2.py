import metnum
import argparse
import pandas as pd

# Hiperparámetros óptimos
alpha = 40
k = 5


def run(method, train, test, output):
    with open(output, 'w') as output:
        dataTrain = pd.read_csv(train)
        dataTest = pd.read_csv(test)

        if method == 1:
            res = run_pca(dataTrain, dataTest)
        else:
            res = run_no_pca(dataTrain, dataTest)

        result = 'ImageId,Label\n'
        i = 1

        for x in res:
            result += "%s,%s\n" % (i, int(x))
            i += 1

        output.write(result)

    return
    # pd.DataFrame(res).to_csv(output)


def run_pca(dfTrain, dataTest):
    dataTrain = dfTrain[dfTrain.columns[1:]].values
    labelTrain = dfTrain["label"].values.reshape(-1, 1)
    dataTest = dataTest.values

    pca = metnum.PCA(alpha)
    pca.fit(dataTrain)

    dataTrain = pca.transform(dataTrain)
    dataTest = pca.transform(dataTest)

    clf = metnum.KNNClassifier(k)
    clf.fit(dataTrain, labelTrain)
    pred = clf.predict(dataTest)

    return pred


def run_no_pca(dfTrain, dataTest):
    dataTrain = dfTrain[dfTrain.columns[1:]].values
    labelTrain = dfTrain["label"].values.reshape(-1, 1)
    dataTest = dataTest.values

    clf = metnum.KNNClassifier(k)
    clf.fit(dataTrain, labelTrain)
    pred = clf.predict(dataTest)

    return pred


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("-m", type=int)
    parser.add_argument("-i", type=str)
    parser.add_argument("-q", type=str)
    parser.add_argument("-o", type=str)

    args = parser.parse_args()

    run(args.m, args.i, args.q, args.o)
