function Singleton() {
    if (Singleton.instance)
        return Singleton.instance;

    Singleton.instance = this;

    this.getData = function () {
        return this;
    };
}

