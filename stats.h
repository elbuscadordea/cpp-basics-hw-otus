//
// Created by elbus on 2026-10-27.
//
#pragma once

namespace stats {
    class IStatistics {
    public:
        virtual ~IStatistics() {
        }

        virtual void update(double next) = 0;

        virtual double eval() const = 0;

        virtual const char *name() const = 0;
    };

    class Min : public IStatistics {
    public:
        Min();

        void update(double next) override;

        double eval() const override;

        const char *name() const override;

    private:
        double m_min;
    };

    class Max : public IStatistics {
    public:
        Max();

        void update(double next) override;

        double eval() const override;

        const char *name() const override;

    private:
        double m_max;
    };


    class Mean : public IStatistics {
    public:
        Mean();

        void update(double next) override;

        double eval() const override;

        const char *name() const override;

    private:
        int count;
        double mean;
    };


    class STD : public IStatistics {
    public:
        STD();

        void update(double next) override;

        double eval() const override;

        const char *name() const override;

    private:
        int count;
        double mean;
        double m2;
    };

} // namespace stats
