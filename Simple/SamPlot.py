import pylab


def sam_plot(xs, ys, label):
    pylab.plot(xs, ys, label=label)

def save_plot(xlabel, ylabel, title, filename):
    pylab.legend()

    pylab.xlabel(xlabel)
    pylab.ylabel(ylabel)
    pylab.title(title)
    pylab.grid(True)
    pylab.savefig(filename)

    pylab.clf()
    #pylab.show()
